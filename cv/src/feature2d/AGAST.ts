import {Image} from '../core/Image';
import {Keypoint} from '../core/Keypoint';
import {FAST} from './FAST';

export class AGAST
{
    private fast = new FAST();
    private _nms: boolean = false;

    // Getter and setter functions
    get T(): number { return this.fast.T; }
    set T(T: number) { this.fast.T = T; }

    get S(): number { return this.fast.S; }
    set S(S: number) { this.fast.S = S; }

    get mask(): number { return this.fast.mask; }
    set mask(mask: number) { this.fast.mask = mask; }

    get nms(): boolean { return this._nms; }
    set nms(nms: boolean) { this._nms = nms; }

    get subpixel(): boolean { return this.fast.subpixel; }
    set subpixel(subpixel: boolean) { this.fast.subpixel = subpixel; }


    constructor()
    {
    }


    public getScores(image: Image) {
        this.fast.nms = false;
        return this.fast.getScores(image);
    }


    public getFeatures(image: Image): Keypoint[]
    {
        this.fast.nms = false;
        const input: Keypoint[] = this.fast.getFeatures(image);

        if (!this.nms) {
            return input;
        }

        const nmsFlags: number[] = [];
        for (let i = 0; i < input.length; i++) {
            nmsFlags[i] = -1;
        }

        let lastRow = 0;
        let nextLastRow = 0;
        let lastRowInd = 0;
        let nextLastRowInd = 0;

        // Non-maximum suppression
        for (let i = 0; i < input.length; i++) {
            let t;
            const current = input[i];

            // Check above
            if (lastRow + 1 < current.y) {
                lastRow = nextLastRow;
                lastRowInd = nextLastRowInd;
            }

            if (nextLastRow !== current.y) {
                nextLastRow = current.y;
                nextLastRowInd = i;
            }

            if (lastRow + 1 === current.y) {
                while (input[lastRowInd].x < current.x &&
                       input[lastRowInd].y === lastRow) {
                    lastRowInd++;
                }

                if (input[lastRowInd].x === current.x && lastRowInd !== i) {
                    let w = lastRowInd;
                    while (nmsFlags[w] !== -1) {
                        w = nmsFlags[w];
                    }
                    if (input[i].score < input[w].score) {
                        nmsFlags[i] = w;
                    } else {
                        nmsFlags[w] = i;
                    }
                }
            }

            // Check left
            t = i - 1;
            if (i !== 0 && input[t].y === current.y && input[t].x + 1 === current.x) {
                const currMaxAboveInd = nmsFlags[i];

                while (nmsFlags[t] !== -1) {
                    t = nmsFlags[t];
                }

                if (currMaxAboveInd === -1) {
                    if (t !== i) {
                        if (input[i].score < input[t].score) {
                            nmsFlags[i] = t;
                        } else {
                            nmsFlags[t] = i;
                        }
                    }
                } else {
                    if (t !== currMaxAboveInd) {
                        if (input[currMaxAboveInd].score < input[t].score) {
                            nmsFlags[currMaxAboveInd] = t;
                            nmsFlags[i] = t;
                        } else {
                            nmsFlags[t] = currMaxAboveInd;
                            nmsFlags[i] = currMaxAboveInd;
                        }
                    }
                }
            }
        }

        const corners = [];
        for (let i = 0; i < input.length; i++) {
            if (nmsFlags[i] === -1) {
                corners.push(input[i]);
            }
        }

        return corners;
    }
}
