import {Image} from '../core/Image'
import {ImageImageData} from '../core/ImageImageData'
import {ScalePyramid} from '../imgproc/ScalePyramid'
import {Filter, ShaderInfo} from '../core/Filter'

export interface Point
{
    x: number
    y: number
}


export class LK extends Filter
{
    private _scaleP: ScalePyramid;
    private _scaleN: ScalePyramid;
    
    constructor(Lm: number)
    {
        super();
        this.setupShaders();
        
        this._scaleP = new ScalePyramid();
        this._scaleN = new ScalePyramid();    
    }

    
    /**
     * Perhaps we can use a shader that has three input textures.
     *  - The first contains input coordinates
     *  - The second contains the prev image 
     *    (do we need access to the complete image, 
     *     or will a single value per coordinate suffice?)
     *  - The third contains the next image
     * 
     * For now we will implement LK in software
     */
    calcOpticalFlowPyrLK(prevImg: Image[], nextImg: Image[], prevPtr: Point[], winSize: number, Lm: number = 3)
    {
        if(prevImg.length != nextImg.length)
            throw "Previous and next image pyramids must have the same length.";
        
        winSize = (winSize - 1) / 2;
        
        var prevImgID: ImageImageData[] = [];
        var nextImgID: ImageImageData[] = [];
        
        if(prevImg.length == 1) {
            this._scaleP.buildPyramid(prevImg[0], Lm);
            prevImgID = this._scaleP.asPixelData();
        
            this._scaleN.buildPyramid(nextImg[0], Lm);
            nextImgID = this._scaleN.asPixelData();
        } else {
            for(var i = 0; i < prevImg.length; i++) {
                prevImgID[i] = prevImg[i].asImageData();
                nextImgID[i] = nextImg[i].asImageData();
            }
        }
        
        // Perform scaling if required
        /**
         * According to the PDF, blurring is required:
         *  1/4 centre + 1/8 top/left/bottom/right + 1/16 corners
         * Scaling is always 2:1
         */
        var prevImgD: ImageData[] = [];
        var nextImgD: ImageData[] = [];

        for(var i = 0; i < prevImg.length; i++) {
            prevImgD[i] = prevImgID[i].getImageData();
            nextImgD[i] = nextImgID[i].getImageData();
        }
 
        
        function sample(d: ImageData, x: number, y: number) {            
            var offset = (y * d.width + x) * 4.0;
            return d.data[offset];
        }
        
        
        /**
         * Derivatives of Il, eqs. 11, 19, and 20
         */
        function derivative(d: ImageData, x: number, y: number): Point 
        {
            var Ix =  -3 * sample(d, x - 1, y - 1) +  3 * sample(d, x + 1, y - 1) +
                     -10 * sample(d, x - 1, y)     + 10 * sample(d, x + 1, y) +
                      -3 * sample(d, x - 1, y + 1) +  3 * sample(d, x + 1, y + 1);            

            var Iy =  -3 * sample(d, x - 1, y - 1) +  3 * sample(d, x - 1, y + 1) +
                     -10 * sample(d, x, y - 1)     + 10 * sample(d, x, y + 1) +
                      -3 * sample(d, x + 1, y - 1) +  3 * sample(d, x + 1, y + 1);            

            return { x: Ix, y: Iy };        
        }
        
        function gradient(d: ImageData, px: number, py: number, wx: number, wy: number)
        {
            var ix = Math.floor(px);
            var rx = px - ix;
            
            var iy = Math.floor(py);
            var ry = py - iy;
            
            var i00 = (1 - rx) * (1 - ry);
            var i01 = (1 - rx) * ry;
            var i10 = rx * (1 - ry);
            var i11 = rx * ry;

            var G = [0, 0, 0];
           
            for(var x = ix - wx; x <= ix + wx; x++) {
                for(var y = iy - wy; y <= iy + wy; y++) {                    
                    var I00 = derivative(d, x, y);
                    var I10 = derivative(d, x + 1, y);
                    var I01 = derivative(d, x, y + 1);
                    var I11 = derivative(d, x + 1, y + 1);      
                    
                    var I = { x: Math.round(I00.x * i00 + I10.x * i10 + I01.x * i01 + I11.x * i11), 
                              y: Math.round(I00.y * i00 + I10.y * i10 + I01.y * i01 + I11.y * i11) };

                    G[0] += I.x * I.x;
                    G[1] += I.x * I.y;
                    G[2] += I.y * I.y;
                }
            }
            return G;
        }
        
        function inverse(g: number[])
        {
            var det = (1.0 / (g[0] * g[2] - g[1] * g[1]));
            return [det * g[2], -det * g[1], det * g[0]];
        }
        
        //difference(p, n, iP, iN);
        function difference(p: ImageData, n: ImageData, x, y, iP, iN)
        {        
            // interpolate next - interpolate previous
            var I = (32.0 * (
                iP.w00 * sample(p, iP.ix + x, iP.iy + y) + 
                iP.w10 * sample(p, iP.ix + x + 1, iP.iy + y) + 
                iP.w01 * sample(p, iP.ix + x, iP.iy + y + 1) + 
                iP.w11 * sample(p, iP.ix + x + 1, iP.iy + y + 1)));
                
            var J = (32.0 * (
                iN.w00 * sample(n, iN.ix + x, iN.iy + y) +
                iN.w10 * sample(n, iN.ix + x + 1, iN.iy + y) +
                iN.w01 * sample(n, iN.ix + x, iN.iy + y + 1) +
                iN.w11 * sample(n, iN.ix + x + 1, iN.iy + y + 1)
            ));
            
            return Math.round(J) - Math.round(I);
        }
        
        
        function computeWeights(px, py)
        {
            var result = {
                ix: Math.floor(px),
                iy: Math.floor(py),
                rx: undefined,
                ry: undefined,
                w00: undefined, w10: undefined, w01: undefined, w11: undefined
            };
            
            result.rx = px - result.ix;
            result.ry = py - result.iy;
            
            result.w00 = (1 - result.rx) * (1 - result.ry);
            result.w01 = (1 - result.rx) * result.ry;
            result.w10 = result.rx * (1 - result.ry);
            result.w11 = result.rx * result.ry;
            
            for(var i = 0; i < prevImgID.length; i++) {
                prevImgID[i].release();
                nextImgID[i].release();
            }
            
            return result;
        }
        
        
        function mismatch(p: ImageData, n: ImageData, px: number, py: number, wx: number, wy: number, v: Point) 
        {
            var b = [0, 0];

            var iP = computeWeights(px, py);
            var iN = computeWeights(px + v.x, py + v.y);
 
            for(var y = -wy; y <= wy; y++) {
               for(var x = -wx; x <= wx; x++) {
                    var diff = difference(p, n, x, y, iP, iN);
               
                    var I00 = derivative(p, iP.ix + x, iP.iy + y);
                    var I10 = derivative(p, iP.ix + x + 1, iP.iy + y);
                    var I01 = derivative(p, iP.ix + x, iP.iy + y + 1);
                    var I11 = derivative(p, iP.ix + x + 1, iP.iy + y + 1);      
                    
                    var I = { x: Math.round(I00.x * iP.w00 + I10.x * iP.w10 + I01.x * iP.w01 + I11.x * iP.w11), 
                              y: Math.round(I00.y * iP.w00 + I10.y * iP.w10 + I01.y * iP.w01 + I11.y * iP.w11) };

                    b[0] += diff * I.x;
                    b[1] += diff * I.y;
                }
            }

            b[0] /= Math.pow(2, 20);
            b[1] /= Math.pow(2, 20);
                        
            return b;
        }
        
        var K = 20;
        
        // Initialize pyramidal guess (eq. 8)
        var gL: number[] = [0, 0];
        var u = prevPtr[0];

        var flt_scale = 1/Math.pow(2, 20);

        // Initialize iterative LK
        var v: Point = { x: 0, y: 0 };

        // Loop over levels
        for(let L = Lm - 1; L >= 0; L--) {
            // Location of point u on image IL (eq. 5)
            var uL = { x: u.x / Math.pow(2, L), y: u.y / Math.pow(2, L) };

            // Gradient matrix
            var G = gradient(prevImgD[L], uL.x, uL.y, winSize, winSize);
            G[0] *= flt_scale;
            G[1] *= flt_scale;
            G[2] *= flt_scale;
            
            var Gi = inverse(G);
            
            for(var k = 0; k < K; k++) {
                var b = mismatch(prevImgD[L], nextImgD[L], uL.x, uL.y, winSize, winSize, v);

                var n = {
                    x: -(Gi[0] * b[0] + Gi[1] * b[1]),
                    y: -(Gi[1] * b[0] + Gi[2] * b[1]) };
                
                v = { x: v.x + n.x, y: v.y + n.y };                
            }
                        
            v.x *= 2;
            v.y *= 2;
        }
        
        var v = { x: u.x + v.x / 2, y: u.y + v.y / 2 }
        
        /**
         * nextPts: nx2 matrix new positions of input features
         * status: nx1 vector: 1 if feature was found, 0 otherwise
         * err: not supported, at the moment undefined
         */
        return {
            nextPts: [v],
            status: undefined,
            err: undefined    
        };
    }
}