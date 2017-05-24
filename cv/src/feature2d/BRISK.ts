
import {Image} from '../core/Image';
import {Keypoint} from '../core/Keypoint'

import {Scale} from '../imgproc/Scale';

import {AGAST} from './AGAST';
import {subPixel2D} from './BRISKUtility';


interface ScoreMinMaxResult
{
    ismax: boolean
    score?: number
    
    x?: number,
    y?: number,
    
    deltax?: number
    deltay?: number
    
    scale?: number
}


class BRISKLayer
{   
    private _debug: boolean = false;
    
    private _basicSize: number = 12.0;
    private _layer: number;
    
    private _scale: number;
    private _offset: number = 0.0;
    private _fast: AGAST;
    private _fast58: AGAST;
    private _T;
    
    // 0 for octave, 1 for inter-octave
    private _mode;
    
    protected _below: BRISKLayer;
    protected _above: BRISKLayer;
    
    private _scores: ImageData;
    private _scores58: ImageData;
     

    constructor(mode: number, scale: number, below: BRISKLayer, index: number)
    {
        this._layer = index;
        
        // Create linked list of layers``
        this._below = below;
        
        if(this._below !== undefined)
            this._below._above = this;
        
        // Setup scales
        this._scale = scale;
        this._mode = mode;
        
        // Initialize FAST feature detector
        this._fast = new AGAST();
        
        this._fast.T = 50.0;               
        this._fast.mask = 16;
        this._fast.nms = false;
        this._fast.subpixel = true;
        this._fast.S = 9;      
        
        // Setup FAST 5 8 for the layer below    
        if(this._below === undefined) {
            this._fast58 = new AGAST();
            this._fast58.T = 50.0;
            this._fast58.mask = 8;
            this._fast58.nms = false;
            this._fast58.subpixel = true;
            this._fast58.S = 5;
        }      
    }


    get T(): number { return this._T; }
    set T(T: number) { this._T = T; this._fast.T = T; }
    
    get scale(): number { return this._scale; }

    set above(layer: BRISKLayer) { this._above = layer; }
    set below(layer: BRISKLayer) { this._below = layer; }

    /**
     * Apply gaussian smoothing using a 3x3 kernel.
     */
    private smoothed(x: number, y: number): number
    {        
        var offset = 4 * (y * this._scores.width + x) + 1;

        var l = this._scores.width * 4;
        var w = [1,2,1,2,4,2,1,2,1];
        var d = [-l-4, -l, -l+4, -4, 0, 4, l-4, l, l+4];
        var s = 0;                
        
        for(var i = 0; i < d.length; i++) {
            s += w[i] * this._scores.data[offset + d[i]];
        }

        return s;
    }
    
    
    /**
     * Returns the AGAST score given (x, y) coordinates.
     */
    private getAgastScore(x: number, y: number, threshold_in: number): number
    {       
        var offset = 4 * (y * this._scores.width + x);
        var score = this._scores.data[offset + 1];
                
        if(score > 2) return score;
        this._scores.data[offset + 1] = this._scores.data[offset];
        
        return this._scores.data[offset];
    }
    
    
    /**
     * Returns interpolated agast scores based on a 2x2 window.
     */
    public getAgastScoref(xf: number, yf: number, threshold_in: number, scale_in?: number)
    {
        if(scale_in === undefined) scale_in = 1.0;
        
        if(scale_in <= 1.0) {
            var x = Math.floor(xf);
            var y = Math.floor(yf);
            
            var rx1 = xf - x;
            var rx = 1.0 - rx1;
            
            var ry1 = yf - y;
            var ry = 1.0 - ry1;
            
           
            return Math.floor(rx  * ry * this.getAgastScore(x, y, threshold_in) +
                    rx1 * ry * this.getAgastScore(x + 1, y, threshold_in) +
                    rx1 * ry1 * this.getAgastScore(x + 1, y + 1, threshold_in) +
                    rx  * ry1 * this.getAgastScore(x, y + 1, threshold_in));
        }
        
        return 0.0;
    }               
    
    
    private getAgastScore_5_8(x: number, y: number, threshold: number)
    {
        if(x < 2 || y < 2) return 0;
        if(x > this._scores58.width - 2 || y > this._scores58.height - 2) return 0;
                
        var offset = 4 * (y * this._scores58.width + x);
        var score = this._scores58.data[offset];
                
        if(score < threshold)
            return 0;
        return score;
    }    
    
    
    setImage(image: Image): void
    {
        var scores = this._fast.getScores(image);
        this._scores = scores.asImageData().getImageData();
        
        if(this._below === undefined) {
            this._scores58 = this._fast58.getScores(image).asImageData().getImageData();
        }
    }
    
    
    isMax2D(i: number): boolean
    {      
        var line = 4 * this._scores.width;
        var deltas = [-line - 4, -line, -line + 4, -4, +4, line - 4, line, line + 4];
        
        // Reject if not maximum in 3x3 area
        for(var j = 0; j < deltas.length; j++) {
            if(this._scores.data[i] < this._scores.data[i + deltas[j]]) { return false; }
        }

        // Pixel coordinates
        var x = (i/4) % this._scores.width;
        var y = Math.floor((i/4) / this._scores.width);                
            
        // If shared maximum, smooth scores
        for(var j = 0; j < deltas.length; j++) {
            if(this._scores.data[i] == this._scores.data[i + deltas[j]]) {
                // Other coordinates
                var i_d = i + deltas[j];
                var x_d = (i_d / 4) % this._scores.width;
                var y_d = Math.floor((i_d / 4) / this._scores.width);
                
                // Compute smoothed scores
                var s_c = this.smoothed(x, y);
                var s_c_d = this.smoothed(x_d, y_d);

                if(s_c < s_c_d) 
                    return false;
            } 
        }
        
        return true;
    }
    
    
    getScoreMaxAbove(x_layer: number, y_layer: number, threshold: number): ScoreMinMaxResult
    {       
        var x_1, x1, y_1, y1;
                        
        if(this._mode == 0.0) {
            x_1 = (4.0 * x_layer - 1 - 2) / 6.0;
            x1 = (4.0 * x_layer - 1 + 2) / 6.0;
            y_1 = (4.0 * y_layer - 1 - 2) / 6.0;
            y1 = (4.0 * y_layer - 1 + 2) / 6.0;
        } else if(this._mode == 1.0) {
            x_1 = (6.0 * x_layer - 1 - 3) / 8.0;
            x1 = (6.0 * x_layer - 1 + 3) / 8.0;
            y_1 = (6.0 * y_layer - 1 - 3) / 8.0;
            y1 = (6.0 * y_layer - 1 + 3) / 8.0;            
        } else {
            throw "Unsupported scale";
        }       
        
        var max_x = Math.floor(x_1 + 1);
        var max_y = Math.floor(y_1 + 1);
        
        /**
         * Check the first row
         */
        var tmp_max;
        var maxval = this._above.getAgastScoref(x_1, y_1, 1.0);
        if(maxval > threshold)
            return { ismax: false, score: maxval };
        
        for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._above.getAgastScoref(x, y_1, 1.0);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > maxval) {
                maxval = tmp_max;
                max_x = x;
            }
        }
        
        tmp_max = this._above.getAgastScoref(x1, y_1, 1.0);
        if(tmp_max > threshold)
            return { ismax: false, score: 0.0 };
        if(tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x1);
        }
        
        /**
         * Middle rows
         */
        for(var y = Math.floor(y_1) + 1; y <= Math.floor(y1); y++) {
            
            tmp_max = this._above.getAgastScoref(x_1, y, 1.0);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > maxval) {
                maxval = tmp_max;
                max_x = Math.floor(x_1 + 1);
                max_y = y;
            }
            
            for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
                tmp_max = this._above.getAgastScore(x, y, 1.0);
                if(tmp_max > threshold)
                    return { ismax: false, score: 0.0 };
                if(tmp_max > maxval) {
                    maxval = tmp_max;
                    max_x = x;
                    max_y = y;
                }
            }
            
            tmp_max = this._above.getAgastScoref(x1, y, 1.0);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > maxval) {
                maxval = tmp_max;
                max_x = Math.floor(x1);
                max_y = y;
            }
        }
        
        /**
         * Bottom row
         */
        tmp_max = this._above.getAgastScoref(x_1, y1, 1.0);
        //if(tmp_max > threshold)
            //return { ismax: false, score: 0.0 };
        if(tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x_1 + 1);
            max_y = Math.floor(y1);
        }
        
        for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._above.getAgastScoref(x, y1, 1.0);
            //if(tmp_max > threshold)
                //return { ismax: false, score: 0.0 };
            if(tmp_max > maxval) {
                maxval = tmp_max;
                max_x = x;
                max_y = Math.floor(y1);
            }
        }
        
        tmp_max = this._above.getAgastScoref(x1, y1, 1.0);
        //if(tmp_max > threshold)
            //return { ismax: false, score: 0.0 };
        if(tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x1);
            max_y = Math.floor(y1);
        }
        
        /**
         * Perform subpixel refinement
         */
        var s_0_0 = Math.round(this._above.getAgastScoref(max_x - 1, max_y - 1, 1));
        var s_1_0 = Math.round(this._above.getAgastScoref(max_x, max_y - 1, 1));
        var s_2_0 = Math.round(this._above.getAgastScoref(max_x + 1, max_y - 1, 1));       
        var s_0_1 = Math.round(this._above.getAgastScoref(max_x - 1, max_y, 1));
        var s_1_1 = Math.round(this._above.getAgastScoref(max_x, max_y, 1));
        var s_2_1 = Math.round(this._above.getAgastScoref(max_x + 1, max_y, 1));        
        var s_0_2 = Math.round(this._above.getAgastScoref(max_x - 1, max_y + 1, 1));
        var s_1_2 = Math.round(this._above.getAgastScoref(max_x, max_y + 1, 1));
        var s_2_2 = Math.round(this._above.getAgastScoref(max_x + 1, max_y + 1, 1));                
       
        var sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2); 
               
        var rx = max_x + sp.x;
        var ry = max_y + sp.y;
        var dx, dy;
        
        if(this._mode == 0.0) {
            dx = (rx * 6.0 + 1.0) / 4.0 - x_layer;
            dy = (ry * 6.0 + 1.0) / 4.0 - y_layer;
        } else if(this._mode == 1.0) {
            dx = (rx * 8.0 + 1.0) / 6.0 - x_layer;
            dy = (ry * 8.0 + 1.0) / 6.0 - y_layer;
        } else {
            throw "Unsupported scale";
        }

        var returnrefined = true;
        
        if(dx > 1.0001) {
            dx = 1.0;
            returnrefined = false;
        }
        if(dx < -1.0001) {
            dx = -1.0;
            returnrefined = false;
        }
        if(dy > 1.0001) {
            dy = 1.0;
            returnrefined = false;
        }
        if(dy < -1.0001) {
            dy = -1.0;
            returnrefined = false;
        }

        if(returnrefined) {
            return { ismax: true, score: Math.max(maxval, sp.score), deltax: dx, deltay: dy };
        } else {
            return { ismax: true, score: maxval, deltax: dx, deltay: dy };
        }        
    }
    
    
    getScoreMaxBelow(x_layer: number, y_layer: number, threshold: number): ScoreMinMaxResult
    {
        var x_1, x1, y_1, y1;
        
        // Octave
        if(this._mode == 0.0) {
            x_1 = (8.0 * x_layer + 1 - 4) / 6.0;
            x1 = (8.0 * x_layer + 1 + 4) / 6.0;
            y_1 = (8.0 * y_layer + 1 - 4) / 6.0;
            y1 = (8.0 * y_layer + 1 + 4) / 6.0;
            
        // Inter-octave
        } else if(this._mode == 1.0) {
            x_1 = (6.0 * x_layer + 1 - 3) / 4.0;
            x1 = (6.0 * x_layer + 1 + 3) / 4.0;
            y_1 = (6.0 * y_layer + 1 - 3) / 4.0;
            y1 = (6.0 * y_layer + 1 + 3) / 4.0;
        } else {
            throw "Unsupported mode: " + this._mode;
        }                       
        
        var debug = false;
        
        var max_x = Math.floor(x_1 + 1);
        var max_y = Math.floor(y_1 + 1);
        var tmp_max;
                
        /**
         * First row
         */
        var max = this._below.getAgastScoref(x_1, y_1, 1);
        if(max > threshold)
            return { ismax: false, score: 0.0 };
        for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._below.getAgastScoref(x, y_1, 1);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x1);
            }
        }
        tmp_max = this._below.getAgastScoref(x1, y_1, 1);
        if(tmp_max > threshold)
            return { ismax: false, score: 0.0 };
        if(tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x1);
        }
        
        /**
         * Middle rows
         */
        for(var y = Math.floor(y_1) + 1; y <= Math.floor(y1); y++) {
            tmp_max = this._below.getAgastScoref(x_1, Math.floor(y), 1);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x_1 + 1);
                max_y = y;
            }
            for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
                tmp_max = this._below.getAgastScoref(x, y, 1);
                if(tmp_max > threshold)
                    return { ismax: false, score: 0.0 };
                if(tmp_max == max) {
                    var t1 = Math.floor(2.0 *
                        (this._below.getAgastScoref(x - 1, y, 1)     + this._below.getAgastScoref(x + 1, y, 1) +
                         this._below.getAgastScoref(x,     y + 1, 1) + this._below.getAgastScoref(x,     y - 1, 1)) +
                        (this._below.getAgastScoref(x + 1, y + 1, 1) + this._below.getAgastScoref(x - 1, y + 1, 1) +
                         this._below.getAgastScoref(x + 1, y - 1, 1) + this._below.getAgastScoref(x - 1, y - 1, 1)));

                    var t2 = Math.floor(2.0 * 
                        (this._below.getAgastScoref(max_x - 1, max_y, 1) + this._below.getAgastScoref(max_x + 1, max_y, 1) +
                         this._below.getAgastScoref(max_x, max_y + 1, 1) + this._below.getAgastScoref(max_x, max_y - 1, 1)) +
                        (this._below.getAgastScoref(max_x + 1, max_y + 1, 1) + this._below.getAgastScoref(max_x - 1, max_y + 1, 1) +
                         this._below.getAgastScoref(max_x + 1, max_y - 1, 1) +
                         this._below.getAgastScoref(max_x - 1, max_y - 1, 1)));
                                             
                    if(t1 > t2) {
                        max_x = x;
                        max_y = y;
                    }
                }
                
                if(tmp_max > max) {
                    max = tmp_max;
                    max_x = x;
                    max_y = y;
                }
            }            
            tmp_max = this._below.getAgastScoref(x1, Math.floor(y), 1);
            if(tmp_max > threshold)
                return { ismax: false, score: 0.0 };
            if(tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x1);
                max_y = y;
            }            
        }
        
        /**
         * Last row
         */
        tmp_max = this._below.getAgastScoref(x_1, y1, 1);
        if(tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x_1 + 1);
            max_y = Math.floor(y1);            
        }
        for(var x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._below.getAgastScoref(x, y1, 1);
            if(tmp_max > max) {
                max = tmp_max;
                max_x = x;
                max_y = Math.floor(y1);
            }
        }
        tmp_max = this._below.getAgastScoref(x1, y1, 1);
        if(tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x1);
            max_y = Math.floor(y1);
        }
        
        /**
         * Sub pixel refinement
         */
        var s_0_0 = Math.round(this._below.getAgastScoref(max_x - 1, max_y - 1, 1));
        var s_1_0 = Math.round(this._below.getAgastScoref(max_x, max_y - 1, 1));
        var s_2_0 = Math.round(this._below.getAgastScoref(max_x + 1, max_y - 1, 1));       
        var s_0_1 = Math.round(this._below.getAgastScoref(max_x - 1, max_y, 1));
        var s_1_1 = Math.round(this._below.getAgastScoref(max_x, max_y, 1));
        var s_2_1 = Math.round(this._below.getAgastScoref(max_x + 1, max_y, 1));        
        var s_0_2 = Math.round(this._below.getAgastScoref(max_x - 1, max_y + 1, 1));
        var s_1_2 = Math.round(this._below.getAgastScoref(max_x, max_y + 1, 1));
        var s_2_2 = Math.round(this._below.getAgastScoref(max_x + 1, max_y + 1, 1));                
       
        var sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);         
        
        var rx = max_x + sp.x;
        var ry = max_y + sp.y;
        var dx, dy;
        
        // Octave
        if(this._mode == 0.0) {
            dx = (rx * 6.0 + 1.0) / 8.0 - x_layer;
            dy = (ry * 6.0 + 1.0) / 8.0 - y_layer;
        
        // Inter-octave
        } else if(this._mode == 1.0) {
            dx = (rx * 4.0 - 1.0) / 6.0 - x_layer;
            dy = (ry * 4.0 - 1.0) / 6.0 - y_layer;
        } else {
            throw "Unsupported mode: " + this._mode;
        }

        var returnrefined = true;
        
        if(dx > 1.0001) {
            dx = 1.0;
            returnrefined = false;
        }
        if(dx < -1.0001) {
            dx = -1.0;
            returnrefined = false;
        }
        if(dy > 1.0001) {
            dy = 1.0;
            returnrefined = false;
        }
        if(dy < -1.0001) {
            dy = -1.0;
            returnrefined = false;
        }

        if(returnrefined) {
            return { ismax: true, score: Math.max(max, sp.score), deltax: dx, deltay: dy };
        } else {
            return { ismax: true, score: max, deltax: dx, deltay: dy };
        }
    }
    
    refine1D(s_05: number, s0: number, s05: number)
    {
        var i_05 = Math.floor(1024.0 * s_05 + 0.5);
        var i0 = Math.floor(1024.0 * s0 + 0.5);
        var i05 = Math.floor(1024.0 * s05 + 0.5);
        
        var three_a = 16 * i_05 - 24 * i0 + 8 * i05;
        
        if(three_a >= 0) {
            if(s0 >= s_05 && s0 >= s05) 
                return { max: s0, scale: 1.0 };
            if(s_05 >= s0 && s_05 >= s05)
                return { max: s_05, scale: 0.75 };
            if(s05 >= s0 && s05 >= s_05)
                return { max: s05, scale: 1.5 };
        }
        
        var three_b = -40 * i_05 + 54 * i0 - 14 * i05;
        var ret_val = -three_b / (2 * three_a);
        
        if(ret_val < 0.75) {
            ret_val = 0.75;
        } else if(ret_val > 1.5) {
            ret_val = 1.5;
        }
        
        var three_c = 24 * i_05 - 27 * i0 + 6 * i05;
        var max = three_c + three_a * ret_val * ret_val + three_b * ret_val;
        
        return { max: max / 3072.0, scale: ret_val};        
    }
    
    
    refine1D_1(s_05: number, s0: number, s05: number)
    {
        var i_05 = Math.floor(1024.0 * s_05 + 0.5);
        var i0 = Math.floor(1024.0 * s0 + 0.5);
        var i05 = Math.floor(1024.0 * s05 + 0.5);
        
        var two_a = 9 * i_05 - 18 * i0 + 9 * i05;
        
        if(two_a >= 0) {
            if(s0 >= s_05 && s0 >= s05) 
                return { max: s0, scale: 1.0 };
            if(s_05 >= s0 && s_05 >= s05)
                return { max: s_05, scale: 2/3 };
            if(s05 >= s0 && s05 >= s_05)
                return { max: s05, scale: 4/3 };
        }
        
        var two_b = -21 * i_05 + 36 * i0 - 15 * i05;
        var ret_val = -two_b / (2 * two_a);
        
        if(ret_val < 2/3) {
            ret_val = 2/3;
        } else if(ret_val > 4/3) {
            ret_val = 4/3;
        }
        
        var two_c = 12 * i_05 - 16 * i0 + 6 * i05;
        var max = two_c + two_a * ret_val * ret_val + two_b * ret_val;
        
        return { max: max / 2048.0, scale: ret_val};
    }
    
    refine1D_2(s_05: number, s0: number, s05: number)
    {
        var i_05 = Math.floor(1024.0 * s_05 + 0.5);
        var i0 = Math.floor(1024.0 * s0 + 0.5);
        var i05 = Math.floor(1024.0 * s05 + 0.5);
        
        var a = 2 * i_05 - 4 * i0 + 2 * i05;
        
        if(a >= 0) {
            if(s0 >= s_05 && s0 >= s05) 
                return { max: s0, scale: 1.0 };
            if(s_05 >= s0 && s_05 >= s05)
                return { max: s_05, scale: 0.7 };
            if(s05 >= s0 && s05 >= s_05)
                return { max: s05, scale: 1.5 };
        }
        
        var b = -5 * i_05 + 8 * i0 - 3 * i05;
        var ret_val = -b / (2 * a);
        
        if(ret_val < 0.7) {
            ret_val = 0.7;
        } else if(ret_val > 1.5) {
            ret_val = 1.5;
        }
        
        var c = 3 * i_05 - 3 * i0 + 1 * i05;
        var max = c + a * ret_val * ret_val + b * ret_val;
        
        return { max: max / 1024.0, scale: ret_val};
    }
    
    refine3D(x: number, y: number): ScoreMinMaxResult
    {
        var center: number = this.getAgastScore(x, y, 1.0);
        
        var max_above: ScoreMinMaxResult = this.getScoreMaxAbove(x, y, center);
                
        if(!max_above.ismax)
            return max_above;
        
        /**
         * Compute maximum on layer below 
         */
        
        var max_below: ScoreMinMaxResult;
        
        // No layer below, so the layer below should be based on FAST 5_8
        if(this._below === undefined) {
            var s_1_1 = this.getAgastScore_5_8(x - 1, y - 1, 1.0);
            var s0_1 = this.getAgastScore_5_8(x, y - 1, 1.0);
            var s1_1 = this.getAgastScore_5_8(x + 1, y - 1, 1.0);            
            var s_10 = this.getAgastScore_5_8(x - 1, y, 1.0);
            var s00 = this.getAgastScore_5_8(x, y, 1.0);
            var s10 = this.getAgastScore_5_8(x + 1, y, 1.0);            
            var s_11 = this.getAgastScore_5_8(x - 1, y + 1, 1.0);
            var s01 = this.getAgastScore_5_8(x, y + 1, 1.0);
            var s11 = this.getAgastScore_5_8(x + 1, y + 1, 1.0);
            
            // Perform subpixel-refinement
            var sp = subPixel2D(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11);
                         
            max_below = {
                ismax: true,
                deltax: sp.x,
                deltay: sp.y,
                score: Math.max(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11)
            }
        } else {
            max_below = this.getScoreMaxBelow(x, y, center);

            if(!max_below.ismax)
                return max_below;
        }
        
        /**
         * Compute patch on this layer
         */
        var s_0_0 = this.getAgastScore(x - 1, y - 1, 1);
        var s_1_0 = this.getAgastScore(x, y - 1, 1);
        var s_2_0 = this.getAgastScore(x + 1, y - 1, 1);       
        var s_0_1 = this.getAgastScore(x - 1, y, 1);
        var s_1_1 = this.getAgastScore(x, y, 1);
        var s_2_1 = this.getAgastScore(x + 1, y, 1);        
        var s_0_2 = this.getAgastScore(x - 1, y + 1, 1);
        var s_1_2 = this.getAgastScore(x, y + 1, 1);
        var s_2_2 = this.getAgastScore(x + 1, y + 1, 1);                        
        var sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);
        var max_layer: ScoreMinMaxResult = { ismax: true, deltax: sp.x, deltay: sp.y, score: sp.score };
        
        /**
         * Calculate relative scale
         */
        var refined1D;
        if(this._below === undefined) {
            refined1D = this.refine1D_2(max_below.score, Math.max(center, max_layer.score), max_above.score);
        } else if(this._mode == 0.0) {
            refined1D = this.refine1D(max_below.score, Math.max(center, max_layer.score), max_above.score);
        } else if(this._mode == 1.0) {
            refined1D = this.refine1D_1(max_below.score, Math.max(center, max_layer.score), max_above.score);
        }

        var x_hat, y_hat;                

        if(this._mode == 0.0) {
            if(refined1D.scale > 1.0) {
                var r0 = (1.5 - refined1D.scale) / 0.5;
                var r1 = 1.0 - r0;
                x_hat = (r0 * max_layer.deltax + r1 * max_above.deltax + x) * this._scale + this._offset;
                y_hat = (r0 * max_layer.deltay + r1 * max_above.deltay + y) * this._scale + this._offset;
            } else {
                if(this._below === undefined) {
                    var r0 = (refined1D.scale - 0.5) / 0.5;
                    var r_1 = 1.0 - r0;
                    x_hat = r0 * max_layer.deltax + r_1 * max_below.deltax + x;
                    y_hat = r0 * max_layer.deltay + r_1 * max_below.deltay + y; 
                } else {
                    var r0 = (refined1D.scale - 0.75) / 0.25;
                    var r_1 = 1.0 - r0;
                    x_hat = (r0 * max_layer.deltax + r_1 * max_below.deltax + x) * this._scale + this._offset;
                    y_hat = (r0 * max_layer.deltay + r_1 * max_below.deltay + y) * this._scale + this._offset;
                }
            }       
        } else if(this._mode == 1.0) {
            if(refined1D.scale > 1.0) {
                var r0 = 4.0 - refined1D.scale * 3.0;
                var r_1 = 1.0 - r0;
            
                x_hat = (r0 * max_layer.deltax + r_1 * max_above.deltax + x) * this._scale + this._offset;
                y_hat = (r0 * max_layer.deltay + r_1 * max_above.deltay + y) * this._scale + this._offset;
            } else {
                var r0 = refined1D.scale * 3.0 - 2.0;
                var r_1 = 1.0 - r0;
                
                x_hat = (r0 * max_layer.deltax + r_1 * max_below.deltax + x) * this._scale + this._offset;
                y_hat = (r0 * max_layer.deltay + r_1 * max_below.deltay + y) * this._scale + this._offset;
            }
        }        
        
        return { ismax: true, score: refined1D.max, scale: refined1D.scale * this._scale,  x: x_hat, y: y_hat };
    }
    
    
    getFeatures(): Keypoint[]
    {
        if(this._scores === undefined) throw "BRISKLayer: Image not set";           
        
        var features = [];
        
        var afterMax2D = 0;

        for(var i = 0; i < this._scores.data.length; i += 4) {
            // Reject scores below threshold
            if(this._scores.data[i] < this._T) 
                continue;

            // Pixel coordinates
            var x = (i/4) % this._scores.width;
            var y = Math.floor((i/4) / this._scores.width); 
            
            if(!this.isMax2D(i)) 
                continue;
 
            afterMax2D++; 
 
            if(this._above !== undefined) {
                var result = this.refine3D(x, y);
                                
                if(!result.ismax)
                    continue;

                if(result.score > this._T) {
                    features.push({
                        x: result.x, 
                        y: result.y,
                        score: result.score,
                        size: this._basicSize * result.scale,
                        layer: this._layer
                    });                    
                }
            } else if(this._below !== undefined) {
                var center = this.getAgastScore(x, y, this._T);
                var max_below = this.getScoreMaxBelow(x, y, center);
                
                if(!max_below.ismax) 
                    continue;
                
                var s_0_0 = this.getAgastScore(x - 1, y - 1, 1);
                var s_1_0 = this.getAgastScore(x, y - 1, 1);
                var s_2_0 = this.getAgastScore(x + 1, y - 1, 1);       
                var s_0_1 = this.getAgastScore(x - 1, y, 1);
                var s_1_1 = this.getAgastScore(x, y, 1);
                var s_2_1 = this.getAgastScore(x + 1, y, 1);        
                var s_0_2 = this.getAgastScore(x - 1, y + 1, 1);
                var s_1_2 = this.getAgastScore(x, y + 1, 1);
                var s_2_2 = this.getAgastScore(x + 1, y + 1, 1);                        
                var sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);
                
                features.push({
                    x: (x + sp.x) * this._scale + this._offset,
                    y: (y + sp.y) * this._scale + this._offset,
                    score: sp.score,
                    size: this._basicSize * this._scale,
                    layer: this._layer
                });
            }                        
            
            // There is only one layer
            if(this._above === undefined && this._below === undefined) {
                // Copy scores in 3x3 area around pixel
                var s_1_1 = this.getAgastScoref(x - 1, y - 1, this._T, 1.0);
                var s0_1 = this.getAgastScoref(x, y - 1, this._T, 1.0);
                var s1_1 = this.getAgastScoref(x + 1, y - 1, this._T, 1.0);
                
                var s_10 = this.getAgastScoref(x - 1, y, this._T, 1.0);
                var s00 = this.getAgastScoref(x, y, this._T, 1.0);
                var s10 = this.getAgastScoref(x + 1, y, this._T, 1.0);
                
                var s_11 = this.getAgastScoref(x - 1, y + 1, this._T, 1.0);
                var s01 = this.getAgastScoref(x, y + 1, this._T, 1.0);
                var s11 = this.getAgastScoref(x + 1, y + 1, this._T, 1.0);
            
                // Perform subpixel-refinement
                var sp = subPixel2D(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11);

                features.push({
                    x: x + sp.x, 
                    y: y + sp.y,
                    score: sp.score,
                    size: this._basicSize,
                    layer: this._layer
                });
            }
        }
        
        return features;            
    }
}



export class BRISK
{
    private _T: number;    
    private _octaveCount: number = 0;    
    private _layers: BRISKLayer[] = [];
        
    private _scale: Scale;
    
    /**
     * Parameters
     */
    private _basicSize = 12.0;
    private _scales = 64;
    private _scalerange = 30.0;
    private _n_rot = 1024;
    
    private _sizeList: number[] = [];
    private _scaleList: number[] = [];
    private _radiusList: number[] = [];
    private _numberList: number[] = [];
    
    get T(): number { return this._T; }
    set T(T: number) { this._T = T; }
    
    get octaveCount(): number { return this._octaveCount; }
    set octaveCount(octaveCount: number) {
        
        var octave = 0;
        var interoctave = 1;
        
        if(octaveCount == 0) {
            this._layers.length = 1;
            this.createLayer(0, octave, 1.0);
            this._layers[0].above = undefined;
            this._octaveCount = octaveCount;
            return;    
        }
                        
        this._layers.length = octaveCount * 2;

        this.createLayer(0, octave, 1.0);
        this.createLayer(1, interoctave, 1.5);

        // Update stages
        for(var i = 2; i < this._layers.length; i += 2) {
            this.createLayer(i + 0, octave, this._layers[i - 2].scale * 2.0);
            this.createLayer(i + 1, interoctave, this._layers[i - 1].scale * 2.0);
        }

        this._octaveCount = octaveCount;
        
        this._layers[this._layers.length - 1].above = undefined;        
    }


    constructor(octaveCount: number = 5, patternScale?: number)
    {
        if(patternScale === undefined) patternScale = 1.0;
        
        // Default number of octaves
        this.octaveCount = octaveCount; 
        this._scale = new Scale();
        
        var f = 0.85 * patternScale;
        this._radiusList = [f * 0, f * 2.9, f * 4.9, f * 7.4, f * 10.8];
        this._numberList = [1, 10, 14, 15, 20];
        
        this.generateKernel(5.85 * patternScale, 8.2 * patternScale);
    }
    
    
    private generateKernel(dMax: number, dMin: number)
    {
        var rings = this._radiusList.length;
        
        var points = 0;
        for(var ring = 0; ring < rings; ring++)
            points += this._numberList[ring];
        
        // Scale disretization
        var lb_scale = Math.log(this._scalerange) / Math.log(2);
        var lb_scale_step = lb_scale / this._scales;
        
        this._scaleList.length = this._scales;
        this._sizeList.length = this._scales;
        
        var sigma_scale = 1.3;
        
        for(var scale = 0; scale < this._scales; scale++) {
            this._scaleList[scale] = Math.pow(2.0, scale * lb_scale_step);
            this._sizeList[scale] = 0;
            
            for(var ring = 0; ring < rings; ring++) {
                for(var num = 0; num < this._numberList[ring]; num++) {
                    //var alpha = num * 2 * Math.PI / n_rot_;
                    var sigma;
                    if(ring == 0) {
                        sigma = sigma_scale * this._scaleList[scale] * 0.5;
                    } else {
                        sigma = sigma_scale * this._scaleList[scale] * this._radiusList[ring] * Math.sin(Math.PI / this._numberList[ring]);
                    }
                    
                    var size = Math.ceil(this._scaleList[scale] * this._radiusList[ring] + sigma) + 1;
                    if(this._sizeList[scale] < size)
                        this._sizeList[scale] = size;
                }
            }
        }              
    }
    
    
    private createLayer(index, mode, scale): BRISKLayer
    {
        var below: BRISKLayer = undefined;

        if(index - 1 in this._layers)
            below = this._layers[index - 1];        

        if(this._layers[index] == undefined)       
            this._layers[index] = new BRISKLayer(mode, scale, below, index);        

        this._layers[index].T = this._T;
        
        return this._layers[index];         
    }
    
    
    public computeKeypointsNoOrientation(image: Image): Keypoint[]
    {                
        var images = [image, this._scale.scale(image, 2.0/3.0)];
        
        this._layers[0].setImage(images[0]);
        
        if(this._layers.length > 1)
            this._layers[1].setImage(images[1]);
        
        for(var i = 2; i < this._layers.length; i += 2) {
            images[0] = this._scale.scale(images[0], 1.0/2.0);
            images[1] = this._scale.scale(images[1], 1.0/2.0);
            
            this._layers[i].setImage(images[0]);
            this._layers[i + 1].setImage(images[1]);
        }


        // Only one layer, just return the features
        if(this._octaveCount == 0) {
            return this._layers[0].getFeatures();
        }

        // Process all layers
        var features = [];
        for(var i = 0; i < this._layers.length; i++) {
            var layerFeatures = this._layers[i].getFeatures();
            console.log("Raw keypoints in layer", i, layerFeatures.length);
            
            Array.prototype.push.apply(features, layerFeatures);
        }
                    
        return features;
    }
    
    
    public computeDescriptorsAndOrientation(image: Image): Keypoint[]
    {
        var keypoints = this.computeKeypointsNoOrientation(image);
        
        //console.log("Keypoints before border:", keypoints.length);
        
        var log2 = 0.693147180559945;
        var scalerange = 30.0;
        var basicSize = 12.0;
        
        var lb_scalerange = Math.log(scalerange) / log2;
        var basicSize06 = 0.6 * basicSize;        
        
        // Remove keypoints close to the border
        keypoints = keypoints.filter(function(keypoint) {
            var scale = Math.min(Math.max(0, Math.floor(this._scales / lb_scalerange * (Math.log(keypoint.size / basicSize06) / log2) + 0.5)), this._scales - 1);            
            var border = this._sizeList[scale];            
            
            if(keypoint.x < border || keypoint.x >= (image.width - border) ||
                keypoint.y < border || keypoint.y >= (image.height - border))
                return false;
                
            return true;
        }.bind(this));
        
        return keypoints;     
    }
    
    
    public getFeatures(image): Keypoint[]
    {
        return this.computeDescriptorsAndOrientation(image);
    }
}
