/**
 * Implementation of Viola-Jones classifier
 *
 * Copyright (C) 2014 Ivar Clemens
 */
import {StageInterface} from './Cascade';
import {HaarClassifier} from './HaarClassifier';
import {IntegralImage} from './IntegralImage';

export class HaarStage
{
    private _stageIdx: number;
    private _classifier: HaarClassifier;

    private _integralImage: IntegralImage = null;

    private _scale: number = undefined;
    private _thresholds: Float64Array;
    private _rects: Int32Array;
    private _cache: Float64Array;

    private _caches: { [ key: string ]: Float64Array };


    set integralImage(integralImage: IntegralImage)
    {
        this._integralImage = integralImage;
        this.updateCache();
    }


    set scale(scale: number)
    {
        if (this._scale === scale) {
            return;
        }

        this._scale = scale;
        this.updateCache();
    }


    constructor(classifier: HaarClassifier, stage: StageInterface, stageIdx: number)
    {
        this._stageIdx = stageIdx;
        this._classifier = classifier;

        this._thresholds = stage.thresholds;
        this._rects = stage.rects;
        this._caches = {};
    }

    /**
     * Updates the scaled rectangle cache. It contains the coordinates of all
     * rectangles at the proper scale.
     */
    public updateCache(): void
    {
        // Only update if both image and scale are set
        if (this._integralImage === null || this._scale === undefined) {
            return;
        }

        const scale: number = this._scale;
        const width: number = this._integralImage.width;

        const key: string = width + 'x' + scale;

        if (!(key in this._caches)) {
            const cache = new Float64Array(this._rects.length);

            // Cache result of scale multiplication and rounding
            for (let i = 0; i < this._rects.length; i += 5) {
                const rectLeft = Math.round(this._rects[i + 0] * scale);
                const rectTop = Math.round(this._rects[i + 1] * scale);
                const rectWidth = Math.round(this._rects[i + 2] * scale);
                const rectHeight = Math.round(this._rects[i + 3] * scale);

                // The cache holds, in order, TL, TR, BL, BR
                cache[i + 0] = rectTop * width + rectLeft;
                cache[i + 1] = cache[i + 0] + rectWidth;

                cache[i + 2] = cache[i + 0] + rectHeight * width;
                cache[i + 3] = cache[i + 2] + rectWidth;

                // The area of a feature changes because of rounding
                // here we compensate for that effect
                const originalArea =  this._rects[i + 2] * this._rects[i + 3];
                const expectedArea = originalArea * (scale * scale);
                const actualArea = rectWidth * rectHeight;

                if (this._rects[i + 4] === 0) {
                    cache[i + 4] = 0;
                } else {
                    cache[i + 4] = this._rects[i + 4] / actualArea * expectedArea;
                }
            }

            this._caches[key] = cache;
            this._cache = cache;

            return;
        }

        this._cache = this._caches[key];
    }


    public classify(ii: (Float32Array | Float64Array), offset: number, stdev: number, invArea: number): boolean
    {
        let sum = 0;

        // 	Loop over all trees
        for (let tt = 0, tr = 0; tr < this._rects.length; tt += 3, tr += 15)
        {
            let rect_sum = 0;

            // Sub rectangle
            for (let sr = 0; sr < 15; sr += 5) {
                const ofs = (tr + sr);

                rect_sum +=
                    (ii[offset + this._cache[ofs + 0]]
                    + ii[offset + this._cache[ofs + 3]]
                    - ii[offset + this._cache[ofs + 1]]
                    - ii[offset + this._cache[ofs + 2]]) * this._cache[ofs + 4];
            }

            rect_sum /= stdev;
            const threshold = this._thresholds[tt + 0] / invArea;

            if (rect_sum < threshold) {
                sum += this._thresholds[tt + 1];
            } else {
                sum += this._thresholds[tt + 2];
            }
        }

        // Terminate if threshold for current stage is not reached
        return sum > this._thresholds[this._thresholds.length - 1];
    }
}
