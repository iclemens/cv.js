import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImageImageData} from '../core/ImageImageData';
import {ScalePyramid} from '../imgproc/ScalePyramid';

export interface Point
{
    x: number;
    y: number;
}


export class LK extends Filter
{
    private scaleP: ScalePyramid;
    private scaleN: ScalePyramid;

    constructor(Lm: number)
    {
        super();
        this.setupShaders();

        this.scaleP = new ScalePyramid();
        this.scaleN = new ScalePyramid();
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
    public calcOpticalFlowPyrLK(prevImg: Image[], nextImg: Image[], prevPtr: Point[], winSize: number, Lm: number = 3)
    {
        if (prevImg.length !== nextImg.length) {
            throw new Error('Previous and next image pyramids must have the same length.');
        }

        winSize = (winSize - 1) / 2;

        let prevImgID: ImageImageData[] = [];
        let nextImgID: ImageImageData[] = [];

        if (prevImg.length === 1) {
            this.scaleP.buildPyramid(prevImg[0], Lm);
            prevImgID = this.scaleP.asPixelData();

            this.scaleN.buildPyramid(nextImg[0], Lm);
            nextImgID = this.scaleN.asPixelData();
        } else {
            for (let i = 0; i < prevImg.length; i++) {
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
        const prevImgD: ImageData[] = [];
        const nextImgD: ImageData[] = [];

        for (let i = 0; i < prevImg.length; i++) {
            prevImgD[i] = prevImgID[i].getImageData();
            nextImgD[i] = nextImgID[i].getImageData();
        }


        function sample(d: ImageData, x: number, y: number) {
            const offset = (y * d.width + x) * 4.0;
            return d.data[offset];
        }


        /**
         * Derivatives of Il, eqs. 11, 19, and 20
         */
        function derivative(d: ImageData, x: number, y: number): Point
        {
            const Ix =  -3 * sample(d, x - 1, y - 1) +  3 * sample(d, x + 1, y - 1) +
                       -10 * sample(d, x - 1, y)     + 10 * sample(d, x + 1, y) +
                        -3 * sample(d, x - 1, y + 1) +  3 * sample(d, x + 1, y + 1);

            const Iy =  -3 * sample(d, x - 1, y - 1) +  3 * sample(d, x - 1, y + 1) +
                       -10 * sample(d, x, y - 1)     + 10 * sample(d, x, y + 1) +
                        -3 * sample(d, x + 1, y - 1) +  3 * sample(d, x + 1, y + 1);

            return { x: Ix, y: Iy };
        }

        function gradient(d: ImageData, px: number, py: number, wx: number, wy: number): number[]
        {
            const ix = Math.floor(px);
            const rx = px - ix;

            const iy = Math.floor(py);
            const ry = py - iy;

            const i00 = (1 - rx) * (1 - ry);
            const i01 = (1 - rx) * ry;
            const i10 = rx * (1 - ry);
            const i11 = rx * ry;

            const G = [0, 0, 0];

            for (let x = ix - wx; x <= ix + wx; x++) {
                for (let y = iy - wy; y <= iy + wy; y++) {
                    const I00 = derivative(d, x, y);
                    const I10 = derivative(d, x + 1, y);
                    const I01 = derivative(d, x, y + 1);
                    const I11 = derivative(d, x + 1, y + 1);

                    const I = { x: Math.round(I00.x * i00 + I10.x * i10 + I01.x * i01 + I11.x * i11),
                                y: Math.round(I00.y * i00 + I10.y * i10 + I01.y * i01 + I11.y * i11) };

                    G[0] += I.x * I.x;
                    G[1] += I.x * I.y;
                    G[2] += I.y * I.y;
                }
            }

            return G;
        }

        function inverse(g: number[]): number[]
        {
            const det = (1.0 / (g[0] * g[2] - g[1] * g[1]));
            return [det * g[2], -det * g[1], det * g[0]];
        }

        function difference(p: ImageData, n: ImageData, x, y, iP, iN)
        {
            // interpolate next - interpolate previous
            const I = (32.0 * (
                iP.w00 * sample(p, iP.ix + x, iP.iy + y) +
                iP.w10 * sample(p, iP.ix + x + 1, iP.iy + y) +
                iP.w01 * sample(p, iP.ix + x, iP.iy + y + 1) +
                iP.w11 * sample(p, iP.ix + x + 1, iP.iy + y + 1)));

            const J = (32.0 * (
                iN.w00 * sample(n, iN.ix + x, iN.iy + y) +
                iN.w10 * sample(n, iN.ix + x + 1, iN.iy + y) +
                iN.w01 * sample(n, iN.ix + x, iN.iy + y + 1) +
                iN.w11 * sample(n, iN.ix + x + 1, iN.iy + y + 1)
            ));

            return Math.round(J) - Math.round(I);
        }


        function computeWeights(px, py)
        {
            const result = {
                ix: Math.floor(px),
                iy: Math.floor(py),
                rx: undefined,
                ry: undefined,
                w00: undefined, w01: undefined, w10: undefined, w11: undefined,
            };

            result.rx = px - result.ix;
            result.ry = py - result.iy;

            result.w00 = (1 - result.rx) * (1 - result.ry);
            result.w01 = (1 - result.rx) * result.ry;
            result.w10 = result.rx * (1 - result.ry);
            result.w11 = result.rx * result.ry;

            for (let i = 0; i < prevImgID.length; i++) {
                prevImgID[i].release();
                nextImgID[i].release();
            }

            return result;
        }


        function mismatch(p: ImageData, n: ImageData, px: number, py: number,
                          wx: number, wy: number, v: Point): number[]
        {
            const b = [0, 0];

            const iP = computeWeights(px, py);
            const iN = computeWeights(px + v.x, py + v.y);

            for (let y = -wy; y <= wy; y++) {
               for (let x = -wx; x <= wx; x++) {
                    const diff = difference(p, n, x, y, iP, iN);

                    const I00 = derivative(p, iP.ix + x, iP.iy + y);
                    const I10 = derivative(p, iP.ix + x + 1, iP.iy + y);
                    const I01 = derivative(p, iP.ix + x, iP.iy + y + 1);
                    const I11 = derivative(p, iP.ix + x + 1, iP.iy + y + 1);

                    const I = { x: Math.round(I00.x * iP.w00 + I10.x * iP.w10 + I01.x * iP.w01 + I11.x * iP.w11),
                                y: Math.round(I00.y * iP.w00 + I10.y * iP.w10 + I01.y * iP.w01 + I11.y * iP.w11) };

                    b[0] += diff * I.x;
                    b[1] += diff * I.y;
                }
            }

            b[0] /= Math.pow(2, 20);
            b[1] /= Math.pow(2, 20);

            return b;
        }

        const K = 20;

        // Initialize pyramidal guess (eq. 8)
        const gL: number[] = [0, 0];
        const u = prevPtr[0];

        const fltScale = 1 / Math.pow(2, 20);

        // Initialize iterative LK
        let v: Point = { x: 0, y: 0 };

        // Loop over levels
        for (let L = Lm - 1; L >= 0; L--) {
            // Location of point u on image IL (eq. 5)
            const uL = { x: u.x / Math.pow(2, L), y: u.y / Math.pow(2, L) };

            // Gradient matrix
            const G = gradient(prevImgD[L], uL.x, uL.y, winSize, winSize);
            G[0] *= fltScale;
            G[1] *= fltScale;
            G[2] *= fltScale;

            const Gi = inverse(G);

            for (let k = 0; k < K; k++) {
                const b = mismatch(prevImgD[L], nextImgD[L], uL.x, uL.y, winSize, winSize, v);

                const n = {
                    x: -(Gi[0] * b[0] + Gi[1] * b[1]),
                    y: -(Gi[1] * b[0] + Gi[2] * b[1]) };

                v = { x: v.x + n.x, y: v.y + n.y };
            }

            v.x *= 2;
            v.y *= 2;
        }

        const vp = { x: u.x + v.x / 2, y: u.y + v.y / 2 };

        /**
         * nextPts: nx2 matrix new positions of input features
         * status: nx1 vector: 1 if feature was found, 0 otherwise
         * err: not supported, at the moment undefined
         */
        return {
            err: undefined,
            nextPts: [vp],
            status: undefined,
        };
    }
}
