import {Image} from '../core/Image';
import {Keypoint} from '../core/Keypoint';
import {AGAST} from './AGAST';
import {subPixel2D} from './BRISKUtility';

export interface IScoreMinMaxResult
{
    ismax: boolean;
    score?: number;

    x?: number;
    y?: number;

    deltax?: number;
    deltay?: number;

    scale?: number;
}

export class BRISKLayer
{
    protected _below: BRISKLayer;
    protected _above: BRISKLayer;

    private debug: boolean = false;

    private basicSize: number = 12.0;
    private layer: number;

    private _scale: number;
    private offset: number = 0.0;
    private fast: AGAST;
    private fast58: AGAST;
    private _T;

    // 0 for octave, 1 for inter-octave
    private mode;

    private scores: ImageData;
    private scores58: ImageData;

    constructor(mode: number, scale: number, below: BRISKLayer, index: number)
    {
        this.layer = index;

        // Create linked list of layers``
        this._below = below;

        if (this._below !== undefined) {
            this._below._above = this;
        }

        // Setup scales
        this._scale = scale;
        this.mode = mode;

        // Initialize FAST feature detector
        this.fast = new AGAST();

        this.fast.T = 50.0;
        this.fast.mask = 16;
        this.fast.nms = false;
        this.fast.subpixel = true;
        this.fast.S = 9;

        // Setup FAST 5 8 for the layer below
        if (this._below === undefined) {
            this.fast58 = new AGAST();
            this.fast58.T = 50.0;
            this.fast58.mask = 8;
            this.fast58.nms = false;
            this.fast58.subpixel = true;
            this.fast58.S = 5;
        }
    }


    get T(): number { return this._T; }
    set T(T: number) { this._T = T; this.fast.T = T; }

    get scale(): number { return this._scale; }

    set above(layer: BRISKLayer) { this._above = layer; }
    set below(layer: BRISKLayer) { this._below = layer; }


    public setImage(image: Image): void
    {
        const scores = this.fast.getScores(image);
        this.scores = scores.asImageData().getImageData();

        if (this._below === undefined) {
            this.scores58 = this.fast58.getScores(image).asImageData().getImageData();
        }
    }


    public isMax2D(i: number): boolean
    {
        const line = 4 * this.scores.width;
        const deltas = [-line - 4, -line, -line + 4, -4, +4, line - 4, line, line + 4];

        // Reject if not maximum in 3x3 area
        for (let j = 0; j < deltas.length; j++) {
            if (this.scores.data[i] < this.scores.data[i + deltas[j]]) { return false; }
        }

        // Pixel coordinates
        const x = (i / 4) % this.scores.width;
        const y = Math.floor((i / 4) / this.scores.width);

        // If shared maximum, smooth scores
        for (let j = 0; j < deltas.length; j++) {
            if (this.scores.data[i] === this.scores.data[i + deltas[j]]) {
                // Other coordinates
                const i_d = i + deltas[j];
                const x_d = (i_d / 4) % this.scores.width;
                const y_d = Math.floor((i_d / 4) / this.scores.width);

                // Compute smoothed scores
                const s_c = this.smoothed(x, y);
                const s_c_d = this.smoothed(x_d, y_d);

                if (s_c < s_c_d) {
                    return false;
                }
            }
        }

        return true;
    }


    public getScoreMaxAbove(x_layer: number, y_layer: number, threshold: number): IScoreMinMaxResult
    {
        let x_1;
        let x1;
        let y_1;
        let y1;

        if (this.mode === 0.0) {
            x_1 = (4.0 * x_layer - 1 - 2) / 6.0;
            x1 = (4.0 * x_layer - 1 + 2) / 6.0;
            y_1 = (4.0 * y_layer - 1 - 2) / 6.0;
            y1 = (4.0 * y_layer - 1 + 2) / 6.0;
        } else if (this.mode === 1.0) {
            x_1 = (6.0 * x_layer - 1 - 3) / 8.0;
            x1 = (6.0 * x_layer - 1 + 3) / 8.0;
            y_1 = (6.0 * y_layer - 1 - 3) / 8.0;
            y1 = (6.0 * y_layer - 1 + 3) / 8.0;
        } else {
            throw new Error('Unsupported scale');
        }

        let max_x = Math.floor(x_1 + 1);
        let max_y = Math.floor(y_1 + 1);

        /**
         * Check the first row
         */
        let tmp_max;
        let maxval = this._above.getAgastScoref(x_1, y_1, 1.0);
        if (maxval > threshold) {
            return { ismax: false, score: maxval };
        }

        for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._above.getAgastScoref(x, y_1, 1.0);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > maxval) {
                maxval = tmp_max;
                max_x = x;
            }
        }

        tmp_max = this._above.getAgastScoref(x1, y_1, 1.0);
        if (tmp_max > threshold) {
            return { ismax: false, score: 0.0 };
        }
        if (tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x1);
        }

        /**
         * Middle rows
         */
        for (let y = Math.floor(y_1) + 1; y <= Math.floor(y1); y++) {
            tmp_max = this._above.getAgastScoref(x_1, y, 1.0);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > maxval) {
                maxval = tmp_max;
                max_x = Math.floor(x_1 + 1);
                max_y = y;
            }

            for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
                tmp_max = this._above.getAgastScore(x, y, 1.0);
                if (tmp_max > threshold) {
                    return { ismax: false, score: 0.0 };
                }
                if (tmp_max > maxval) {
                    maxval = tmp_max;
                    max_x = x;
                    max_y = y;
                }
            }

            tmp_max = this._above.getAgastScoref(x1, y, 1.0);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > maxval) {
                maxval = tmp_max;
                max_x = Math.floor(x1);
                max_y = y;
            }
        }

        /**
         * Bottom row
         */
        tmp_max = this._above.getAgastScoref(x_1, y1, 1.0);
        // if(tmp_max > threshold)
        //     return { ismax: false, score: 0.0 };
        if (tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x_1 + 1);
            max_y = Math.floor(y1);
        }

        for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._above.getAgastScoref(x, y1, 1.0);
            // if(tmp_max > threshold)
            //     return { ismax: false, score: 0.0 };
            if (tmp_max > maxval) {
                maxval = tmp_max;
                max_x = x;
                max_y = Math.floor(y1);
            }
        }

        tmp_max = this._above.getAgastScoref(x1, y1, 1.0);
        // if(tmp_max > threshold)
        //     return { ismax: false, score: 0.0 };
        if (tmp_max > maxval) {
            maxval = tmp_max;
            max_x = Math.floor(x1);
            max_y = Math.floor(y1);
        }

        /**
         * Perform subpixel refinement
         */
        const s_0_0 = Math.round(this._above.getAgastScoref(max_x - 1, max_y - 1, 1));
        const s_1_0 = Math.round(this._above.getAgastScoref(max_x, max_y - 1, 1));
        const s_2_0 = Math.round(this._above.getAgastScoref(max_x + 1, max_y - 1, 1));
        const s_0_1 = Math.round(this._above.getAgastScoref(max_x - 1, max_y, 1));
        const s_1_1 = Math.round(this._above.getAgastScoref(max_x, max_y, 1));
        const s_2_1 = Math.round(this._above.getAgastScoref(max_x + 1, max_y, 1));
        const s_0_2 = Math.round(this._above.getAgastScoref(max_x - 1, max_y + 1, 1));
        const s_1_2 = Math.round(this._above.getAgastScoref(max_x, max_y + 1, 1));
        const s_2_2 = Math.round(this._above.getAgastScoref(max_x + 1, max_y + 1, 1));

        const sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);

        const rx = max_x + sp.x;
        const ry = max_y + sp.y;
        let dx;
        let dy;

        if (this.mode === 0.0) {
            dx = (rx * 6.0 + 1.0) / 4.0 - x_layer;
            dy = (ry * 6.0 + 1.0) / 4.0 - y_layer;
        } else if (this.mode === 1.0) {
            dx = (rx * 8.0 + 1.0) / 6.0 - x_layer;
            dy = (ry * 8.0 + 1.0) / 6.0 - y_layer;
        } else {
            throw new Error('Unsupported scale');
        }

        let returnrefined = true;

        if (dx > 1.0001) {
            dx = 1.0;
            returnrefined = false;
        }
        if (dx < -1.0001) {
            dx = -1.0;
            returnrefined = false;
        }
        if (dy > 1.0001) {
            dy = 1.0;
            returnrefined = false;
        }
        if (dy < -1.0001) {
            dy = -1.0;
            returnrefined = false;
        }

        if (returnrefined) {
            return { ismax: true, score: Math.max(maxval, sp.score), deltax: dx, deltay: dy };
        } else {
            return { ismax: true, score: maxval, deltax: dx, deltay: dy };
        }
    }


    public getScoreMaxBelow(x_layer: number, y_layer: number, threshold: number): IScoreMinMaxResult
    {
        let x_1;
        let x1;
        let y_1;
        let y1;

        // Octave
        if (this.mode === 0.0) {
            x_1 = (8.0 * x_layer + 1 - 4) / 6.0;
            x1 = (8.0 * x_layer + 1 + 4) / 6.0;
            y_1 = (8.0 * y_layer + 1 - 4) / 6.0;
            y1 = (8.0 * y_layer + 1 + 4) / 6.0;

        // Inter-octave
        } else if (this.mode === 1.0) {
            x_1 = (6.0 * x_layer + 1 - 3) / 4.0;
            x1 = (6.0 * x_layer + 1 + 3) / 4.0;
            y_1 = (6.0 * y_layer + 1 - 3) / 4.0;
            y1 = (6.0 * y_layer + 1 + 3) / 4.0;
        } else {
            throw new Error('Unsupported mode: ' + this.mode);
        }

        const debug = false;

        let max_x = Math.floor(x_1 + 1);
        let max_y = Math.floor(y_1 + 1);
        let tmp_max;

        /**
         * First row
         */
        let max = this._below.getAgastScoref(x_1, y_1, 1);
        if (max > threshold) {
            return { ismax: false, score: 0.0 };
        }
        for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._below.getAgastScoref(x, y_1, 1);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x1);
            }
        }
        tmp_max = this._below.getAgastScoref(x1, y_1, 1);
        if (tmp_max > threshold) {
            return { ismax: false, score: 0.0 };
        }
        if (tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x1);
        }

        /**
         * Middle rows
         */
        for (let y = Math.floor(y_1) + 1; y <= Math.floor(y1); y++) {
            tmp_max = this._below.getAgastScoref(x_1, Math.floor(y), 1);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x_1 + 1);
                max_y = y;
            }
            for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
                tmp_max = this._below.getAgastScoref(x, y, 1);
                if (tmp_max > threshold) {
                    return { ismax: false, score: 0.0 };
                }
                if (tmp_max === max) {
                    const t1 = Math.floor(2.0 *
                        (this._below.getAgastScoref(x - 1, y, 1)     + this._below.getAgastScoref(x + 1, y, 1) +
                         this._below.getAgastScoref(x,     y + 1, 1) + this._below.getAgastScoref(x,     y - 1, 1)) +
                        (this._below.getAgastScoref(x + 1, y + 1, 1) + this._below.getAgastScoref(x - 1, y + 1, 1) +
                         this._below.getAgastScoref(x + 1, y - 1, 1) + this._below.getAgastScoref(x - 1, y - 1, 1)));

                    const t2 = Math.floor(2.0 *
                        (this._below.getAgastScoref(max_x - 1, max_y, 1) +
                         this._below.getAgastScoref(max_x + 1, max_y, 1) +
                         this._below.getAgastScoref(max_x, max_y + 1, 1) +
                         this._below.getAgastScoref(max_x, max_y - 1, 1)) +
                        (this._below.getAgastScoref(max_x + 1, max_y + 1, 1) +
                         this._below.getAgastScoref(max_x - 1, max_y + 1, 1) +
                         this._below.getAgastScoref(max_x + 1, max_y - 1, 1) +
                         this._below.getAgastScoref(max_x - 1, max_y - 1, 1)));

                    if (t1 > t2) {
                        max_x = x;
                        max_y = y;
                    }
                }

                if (tmp_max > max) {
                    max = tmp_max;
                    max_x = x;
                    max_y = y;
                }
            }
            tmp_max = this._below.getAgastScoref(x1, Math.floor(y), 1);
            if (tmp_max > threshold) {
                return { ismax: false, score: 0.0 };
            }
            if (tmp_max > max) {
                max = tmp_max;
                max_x = Math.floor(x1);
                max_y = y;
            }
        }

        /**
         * Last row
         */
        tmp_max = this._below.getAgastScoref(x_1, y1, 1);
        if (tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x_1 + 1);
            max_y = Math.floor(y1);
        }
        for (let x = Math.floor(x_1) + 1; x <= Math.floor(x1); x++) {
            tmp_max = this._below.getAgastScoref(x, y1, 1);
            if (tmp_max > max) {
                max = tmp_max;
                max_x = x;
                max_y = Math.floor(y1);
            }
        }
        tmp_max = this._below.getAgastScoref(x1, y1, 1);
        if (tmp_max > max) {
            max = tmp_max;
            max_x = Math.floor(x1);
            max_y = Math.floor(y1);
        }

        /**
         * Sub pixel refinement
         */
        const s_0_0 = Math.round(this._below.getAgastScoref(max_x - 1, max_y - 1, 1));
        const s_1_0 = Math.round(this._below.getAgastScoref(max_x, max_y - 1, 1));
        const s_2_0 = Math.round(this._below.getAgastScoref(max_x + 1, max_y - 1, 1));
        const s_0_1 = Math.round(this._below.getAgastScoref(max_x - 1, max_y, 1));
        const s_1_1 = Math.round(this._below.getAgastScoref(max_x, max_y, 1));
        const s_2_1 = Math.round(this._below.getAgastScoref(max_x + 1, max_y, 1));
        const s_0_2 = Math.round(this._below.getAgastScoref(max_x - 1, max_y + 1, 1));
        const s_1_2 = Math.round(this._below.getAgastScoref(max_x, max_y + 1, 1));
        const s_2_2 = Math.round(this._below.getAgastScoref(max_x + 1, max_y + 1, 1));

        const sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);

        const rx = max_x + sp.x;
        const ry = max_y + sp.y;
        let dx;
        let dy;

        // Octave
        if (this.mode === 0.0) {
            dx = (rx * 6.0 + 1.0) / 8.0 - x_layer;
            dy = (ry * 6.0 + 1.0) / 8.0 - y_layer;

        // Inter-octave
        } else if (this.mode === 1.0) {
            dx = (rx * 4.0 - 1.0) / 6.0 - x_layer;
            dy = (ry * 4.0 - 1.0) / 6.0 - y_layer;
        } else {
            throw new Error('Unsupported mode: ' + this.mode);
        }

        let returnrefined = true;

        if (dx > 1.0001) {
            dx = 1.0;
            returnrefined = false;
        }
        if (dx < -1.0001) {
            dx = -1.0;
            returnrefined = false;
        }
        if (dy > 1.0001) {
            dy = 1.0;
            returnrefined = false;
        }
        if (dy < -1.0001) {
            dy = -1.0;
            returnrefined = false;
        }

        if(returnrefined) {
            return { ismax: true, score: Math.max(max, sp.score), deltax: dx, deltay: dy };
        } else {
            return { ismax: true, score: max, deltax: dx, deltay: dy };
        }
    }

    public refine1D(s_05: number, s0: number, s05: number): {max: number, scale: number}
    {
        const i_05 = Math.floor(1024.0 * s_05 + 0.5);
        const i0 = Math.floor(1024.0 * s0 + 0.5);
        const i05 = Math.floor(1024.0 * s05 + 0.5);

        const threeA = 16 * i_05 - 24 * i0 + 8 * i05;

        if (threeA >= 0) {
            if (s0 >= s_05 && s0 >= s05) {
                return { max: s0, scale: 1.0 };
            } else if (s_05 >= s0 && s_05 >= s05) {
                return { max: s_05, scale: 0.75 };
            } else if (s05 >= s0 && s05 >= s_05) {
                return { max: s05, scale: 1.5 };
            }
        }

        const threeB = -40 * i_05 + 54 * i0 - 14 * i05;
        let result = -threeB / (2 * threeA);

        if (result < 0.75) {
            result = 0.75;
        } else if (result > 1.5) {
            result = 1.5;
        }

        const threeC = 24 * i_05 - 27 * i0 + 6 * i05;
        const max = threeC + threeA * result * result + threeB * result;

        return { max: max / 3072.0, scale: result};
    }

    public refine1D_1(s_05: number, s0: number, s05: number): {max: number, scale: number}
    {
        const i_05 = Math.floor(1024.0 * s_05 + 0.5);
        const i0 = Math.floor(1024.0 * s0 + 0.5);
        const i05 = Math.floor(1024.0 * s05 + 0.5);

        const twoA = 9 * i_05 - 18 * i0 + 9 * i05;

        if (twoA >= 0) {
            if (s0 >= s_05 && s0 >= s05) {
                return { max: s0, scale: 1.0 };
            } else if (s_05 >= s0 && s_05 >= s05) {
                return { max: s_05, scale: 2 / 3 };
            } else if (s05 >= s0 && s05 >= s_05) {
                return { max: s05, scale: 4 / 3 };
            }
        }

        const twoB = -21 * i_05 + 36 * i0 - 15 * i05;
        let result = -twoB / (2 * twoA);

        if (result < 2 / 3) {
            result = 2 / 3;
        } else if (result > 4 / 3) {
            result = 4 / 3;
        }

        const twoC = 12 * i_05 - 16 * i0 + 6 * i05;
        const max = twoC + twoA * result * result + twoB * result;

        return { max: max / 2048.0, scale: result};
    }

    public refine1D_2(s_05: number, s0: number, s05: number): {max: number, scale: number}
    {
        const i_05 = Math.floor(1024.0 * s_05 + 0.5);
        const i0 = Math.floor(1024.0 * s0 + 0.5);
        const i05 = Math.floor(1024.0 * s05 + 0.5);

        const a = 2 * i_05 - 4 * i0 + 2 * i05;

        if (a >= 0) {
            if (s0 >= s_05 && s0 >= s05) {
                return { max: s0, scale: 1.0 };
            } else if (s_05 >= s0 && s_05 >= s05) {
                return { max: s_05, scale: 0.7 };
            } else if (s05 >= s0 && s05 >= s_05) {
                return { max: s05, scale: 1.5 };
            }
        }

        const b = -5 * i_05 + 8 * i0 - 3 * i05;
        let result = -b / (2 * a);

        if (result < 0.7) {
            result = 0.7;
        } else if (result > 1.5) {
            result = 1.5;
        }

        const c = 3 * i_05 - 3 * i0 + 1 * i05;
        const max = c + a * result * result + b * result;

        return { max: max / 1024.0, scale: result};
    }

    public refine3D(x: number, y: number): IScoreMinMaxResult
    {
        const center: number = this.getAgastScore(x, y, 1.0);

        const maxAbove: IScoreMinMaxResult = this.getScoreMaxAbove(x, y, center);

        if (!maxAbove.ismax) {
            return maxAbove;
        }

        /**
         * Compute maximum on layer below
         */

        let maxBelow: IScoreMinMaxResult;

        // No layer below, so the layer below should be based on FAST 5_8
        if (this._below === undefined) {
            const s_1_1 = this.getAgastScore_5_8(x - 1, y - 1, 1.0);
            const s0_1 = this.getAgastScore_5_8(x, y - 1, 1.0);
            const s1_1 = this.getAgastScore_5_8(x + 1, y - 1, 1.0);
            const s_10 = this.getAgastScore_5_8(x - 1, y, 1.0);
            const s00 = this.getAgastScore_5_8(x, y, 1.0);
            const s10 = this.getAgastScore_5_8(x + 1, y, 1.0);
            const s_11 = this.getAgastScore_5_8(x - 1, y + 1, 1.0);
            const s01 = this.getAgastScore_5_8(x, y + 1, 1.0);
            const s11 = this.getAgastScore_5_8(x + 1, y + 1, 1.0);

            // Perform subpixel-refinement
            const sp = subPixel2D(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11);

            maxBelow = {
                deltax: sp.x,
                deltay: sp.y,
                ismax: true,
                score: Math.max(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11)
            };
        } else {
            maxBelow = this.getScoreMaxBelow(x, y, center);

            if (!maxBelow.ismax) {
                return maxBelow;
            }
        }

        /**
         * Compute patch on this layer
         */
        const s_0_0 = this.getAgastScore(x - 1, y - 1, 1);
        const s_1_0 = this.getAgastScore(x, y - 1, 1);
        const s_2_0 = this.getAgastScore(x + 1, y - 1, 1);
        const s_0_1 = this.getAgastScore(x - 1, y, 1);
        const s_1_1 = this.getAgastScore(x, y, 1);
        const s_2_1 = this.getAgastScore(x + 1, y, 1);
        const s_0_2 = this.getAgastScore(x - 1, y + 1, 1);
        const s_1_2 = this.getAgastScore(x, y + 1, 1);
        const s_2_2 = this.getAgastScore(x + 1, y + 1, 1);
        const sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);
        const maxLayer: IScoreMinMaxResult = { ismax: true, deltax: sp.x, deltay: sp.y, score: sp.score };

        /**
         * Calculate relative scale
         */
        let refined1D;
        if (this._below === undefined) {
            refined1D = this.refine1D_2(maxBelow.score, Math.max(center, maxLayer.score), maxAbove.score);
        } else if (this.mode === 0.0) {
            refined1D = this.refine1D(maxBelow.score, Math.max(center, maxLayer.score), maxAbove.score);
        } else if (this.mode === 1.0) {
            refined1D = this.refine1D_1(maxBelow.score, Math.max(center, maxLayer.score), maxAbove.score);
        }

        let x_hat;
        let y_hat;

        if (this.mode === 0.0) {
            if (refined1D.scale > 1.0) {
                const r0 = (1.5 - refined1D.scale) / 0.5;
                const r1 = 1.0 - r0;
                x_hat = (r0 * maxLayer.deltax + r1 * maxAbove.deltax + x) * this._scale + this.offset;
                y_hat = (r0 * maxLayer.deltay + r1 * maxAbove.deltay + y) * this._scale + this.offset;
            } else {
                if (this._below === undefined) {
                    const r0 = (refined1D.scale - 0.5) / 0.5;
                    const r_1 = 1.0 - r0;
                    x_hat = r0 * maxLayer.deltax + r_1 * maxBelow.deltax + x;
                    y_hat = r0 * maxLayer.deltay + r_1 * maxBelow.deltay + y;
                } else {
                    const r0 = (refined1D.scale - 0.75) / 0.25;
                    const r_1 = 1.0 - r0;
                    x_hat = (r0 * maxLayer.deltax + r_1 * maxBelow.deltax + x) * this._scale + this.offset;
                    y_hat = (r0 * maxLayer.deltay + r_1 * maxBelow.deltay + y) * this._scale + this.offset;
                }
            }
        } else if (this.mode === 1.0) {
            if (refined1D.scale > 1.0) {
                const r0 = 4.0 - refined1D.scale * 3.0;
                const r_1 = 1.0 - r0;

                x_hat = (r0 * maxLayer.deltax + r_1 * maxAbove.deltax + x) * this._scale + this.offset;
                y_hat = (r0 * maxLayer.deltay + r_1 * maxAbove.deltay + y) * this._scale + this.offset;
            } else {
                const r0 = refined1D.scale * 3.0 - 2.0;
                const r_1 = 1.0 - r0;

                x_hat = (r0 * maxLayer.deltax + r_1 * maxBelow.deltax + x) * this._scale + this.offset;
                y_hat = (r0 * maxLayer.deltay + r_1 * maxBelow.deltay + y) * this._scale + this.offset;
            }
        }

        return { ismax: true, score: refined1D.max, scale: refined1D.scale * this._scale,  x: x_hat, y: y_hat };
    }


    public getFeatures(): Keypoint[]
    {
        if (this.scores === undefined) {
            throw new Error('BRISKLayer: Image not set');
        }

        const features = [];
        let afterMax2D = 0;

        for (let i = 0; i < this.scores.data.length; i += 4) {
            // Reject scores below threshold
            if (this.scores.data[i] < this._T) {
                continue;
            }

            // Pixel coordinates
            const x = (i / 4) % this.scores.width;
            const y = Math.floor((i / 4) / this.scores.width);

            if (!this.isMax2D(i)) {
                continue;
            }

            afterMax2D++;

            if (this._above !== undefined) {
                const result = this.refine3D(x, y);

                if (!result.ismax) {
                    continue;
                }

                if (result.score > this._T) {
                    features.push({
                        layer: this.layer,
                        score: result.score,
                        size: this.basicSize * result.scale,
                        x: result.x,
                        y: result.y,
                    });
                }
            } else if (this._below !== undefined) {
                const center = this.getAgastScore(x, y, this._T);
                const max_below = this.getScoreMaxBelow(x, y, center);

                if (!max_below.ismax) {
                    continue;
                }

                const s_0_0 = this.getAgastScore(x - 1, y - 1, 1);
                const s_1_0 = this.getAgastScore(x, y - 1, 1);
                const s_2_0 = this.getAgastScore(x + 1, y - 1, 1);
                const s_0_1 = this.getAgastScore(x - 1, y, 1);
                const s_1_1 = this.getAgastScore(x, y, 1);
                const s_2_1 = this.getAgastScore(x + 1, y, 1);
                const s_0_2 = this.getAgastScore(x - 1, y + 1, 1);
                const s_1_2 = this.getAgastScore(x, y + 1, 1);
                const s_2_2 = this.getAgastScore(x + 1, y + 1, 1);
                const sp = subPixel2D(s_0_0, s_0_1, s_0_2, s_1_0, s_1_1, s_1_2, s_2_0, s_2_1, s_2_2);

                features.push({
                    x: (x + sp.x) * this._scale + this.offset,
                    y: (y + sp.y) * this._scale + this.offset,
                    score: sp.score,
                    size: this.basicSize * this._scale,
                    layer: this.layer
                });
            }

            // There is only one layer
            if (this._above === undefined && this._below === undefined) {
                // Copy scores in 3x3 area around pixel
                const s_1_1 = this.getAgastScoref(x - 1, y - 1, this._T, 1.0);
                const s0_1 = this.getAgastScoref(x, y - 1, this._T, 1.0);
                const s1_1 = this.getAgastScoref(x + 1, y - 1, this._T, 1.0);

                const s_10 = this.getAgastScoref(x - 1, y, this._T, 1.0);
                const s00 = this.getAgastScoref(x, y, this._T, 1.0);
                const s10 = this.getAgastScoref(x + 1, y, this._T, 1.0);

                const s_11 = this.getAgastScoref(x - 1, y + 1, this._T, 1.0);
                const s01 = this.getAgastScoref(x, y + 1, this._T, 1.0);
                const s11 = this.getAgastScoref(x + 1, y + 1, this._T, 1.0);

                // Perform subpixel-refinement
                const sp = subPixel2D(s_1_1, s_10, s_11, s0_1, s00, s01, s1_1, s10, s11);

                features.push({
                    layer: this.layer,
                    score: sp.score,
                    size: this.basicSize,
                    x: x + sp.x,
                    y: y + sp.y,
                });
            }
        }

        return features;
    }

    /**
     * Returns interpolated agast scores based on a 2x2 window.
     */
    public getAgastScoref(xf: number, yf: number, threshold_in: number, scale_in?: number): number
    {
        if (scale_in === undefined) { scale_in = 1.0; }

        if (scale_in <= 1.0) {
            const x = Math.floor(xf);
            const y = Math.floor(yf);

            const rx1 = xf - x;
            const rx = 1.0 - rx1;

            const ry1 = yf - y;
            const ry = 1.0 - ry1;

            return Math.floor(rx  * ry * this.getAgastScore(x, y, threshold_in) +
                    rx1 * ry * this.getAgastScore(x + 1, y, threshold_in) +
                    rx1 * ry1 * this.getAgastScore(x + 1, y + 1, threshold_in) +
                    rx  * ry1 * this.getAgastScore(x, y + 1, threshold_in));
        }

        return 0.0;
    }


    /**
     * Apply gaussian smoothing using a 3x3 kernel.
     */
    private smoothed(x: number, y: number): number
    {
        const offset = 4 * (y * this.scores.width + x) + 1;

        const l = this.scores.width * 4;
        const w = [1, 2, 1, 2, 4, 2, 1, 2, 1];
        const d = [-l - 4, -l, -l + 4, -4, 0, 4, l - 4, l, l + 4];
        let s = 0;

        for (let i = 0; i < d.length; i++) {
            s += w[i] * this.scores.data[offset + d[i]];
        }

        return s;
    }


    /**
     * Returns the AGAST score given (x, y) coordinates.
     */
    private getAgastScore(x: number, y: number, threshold_in: number): number
    {
        const offset = 4 * (y * this.scores.width + x);
        const score = this.scores.data[offset + 1];

        if (score > 2) { return score; }
        this.scores.data[offset + 1] = this.scores.data[offset];

        return this.scores.data[offset];
    }


    private getAgastScore_5_8(x: number, y: number, threshold: number): number
    {
        if (x < 2 || y < 2) { return 0; }
        if (x > this.scores58.width - 2 || y > this.scores58.height - 2) { return 0; }

        const offset = 4 * (y * this.scores58.width + x);
        const score = this.scores58.data[offset];

        if (score < threshold) {
            return 0;
        }
        return score;
    }
}
