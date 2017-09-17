import {Image} from '../core/Image';
import {Keypoint} from '../core/Keypoint';

import {Scale} from '../imgproc/Scale';

import {AGAST} from './AGAST';
import {BRISKLayer} from './BRISKLayer';
import {subPixel2D} from './BRISKUtility';

export class BRISK
{
    private _T: number;
    private _octaveCount: number = 0;
    private _layers: BRISKLayer[] = [];

    private _scale: Scale;

    /**
     * Parameters
     */
    private basicSize = 12.0;
    private scales = 64;
    private scalerange = 30.0;
    private nRot = 1024;

    private sizeList: number[] = [];
    private scaleList: number[] = [];
    private radiusList: number[] = [];
    private numberList: number[] = [];

    get T(): number { return this._T; }
    set T(T: number) { this._T = T; }

    get octaveCount(): number { return this._octaveCount; }

    set octaveCount(octaveCount: number) {
        const octave = 0;
        const interoctave = 1;

        if (octaveCount === 0) {
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
        for (let i = 2; i < this._layers.length; i += 2) {
            this.createLayer(i + 0, octave, this._layers[i - 2].scale * 2.0);
            this.createLayer(i + 1, interoctave, this._layers[i - 1].scale * 2.0);
        }

        this._octaveCount = octaveCount;

        this._layers[this._layers.length - 1].above = undefined;
    }


    constructor(octaveCount: number = 5, patternScale?: number)
    {
        if (patternScale === undefined) {
            patternScale = 1.0;
        }

        // Default number of octaves
        this.octaveCount = octaveCount;
        this._scale = new Scale();

        const f = 0.85 * patternScale;
        this.radiusList = [f * 0, f * 2.9, f * 4.9, f * 7.4, f * 10.8];
        this.numberList = [1, 10, 14, 15, 20];

        this.generateKernel(5.85 * patternScale, 8.2 * patternScale);
    }

    public computeKeypointsNoOrientation(image: Image): Keypoint[]
    {
        const images = [image, this._scale.scale(image, 2.0 / 3.0)];

        this._layers[0].setImage(images[0]);

        if (this._layers.length > 1) {
            this._layers[1].setImage(images[1]);
        }

        for (let i = 2; i < this._layers.length; i += 2) {
            images[0] = this._scale.scale(images[0], 1.0 / 2.0);
            images[1] = this._scale.scale(images[1], 1.0 / 2.0);

            this._layers[i].setImage(images[0]);
            this._layers[i + 1].setImage(images[1]);
        }


        // Only one layer, just return the features
        if (this._octaveCount === 0) {
            return this._layers[0].getFeatures();
        }

        // Process all layers
        const features = [];
        for (let i = 0; i < this._layers.length; i++) {
            const layerFeatures = this._layers[i].getFeatures();
            // console.log("Raw keypoints in layer", i, layerFeatures.length);

            Array.prototype.push.apply(features, layerFeatures);
        }

        return features;
    }

    public computeDescriptorsAndOrientation(image: Image): Keypoint[]
    {
        let keypoints = this.computeKeypointsNoOrientation(image);

        // console.log("Keypoints before border:", keypoints.length);

        const log2 = 0.693147180559945;
        const scalerange = 30.0;
        const basicSize = 12.0;

        const lbScaleRange = Math.log(scalerange) / log2;
        const basicSize06 = 0.6 * basicSize;

        // Remove keypoints close to the border
        keypoints = keypoints.filter((keypoint) => {
            const scale = Math.min(Math.max(0,
                Math.floor(this.scales / lbScaleRange *
                           (Math.log(keypoint.size / basicSize06) / log2) + 0.5)), this.scales - 1);
            const border = this.sizeList[scale];

            if (keypoint.x < border || keypoint.x >= (image.width - border) ||
                keypoint.y < border || keypoint.y >= (image.height - border)) {
                return false;
            }

            return true;
        });

        return keypoints;
    }

    public getFeatures(image): Keypoint[]
    {
        return this.computeDescriptorsAndOrientation(image);
    }

    private generateKernel(dMax: number, dMin: number)
    {
        const rings = this.radiusList.length;

        let points = 0;
        for (let ring = 0; ring < rings; ring++) {
            points += this.numberList[ring];
        }

        // Scale disretization
        const lbScale = Math.log(this.scalerange) / Math.log(2);
        const lbScaleStep = lbScale / this.scales;

        this.scaleList.length = this.scales;
        this.sizeList.length = this.scales;

        const sigmaScale = 1.3;

        for (let scale = 0; scale < this.scales; scale++) {
            this.scaleList[scale] = Math.pow(2.0, scale * lbScaleStep);
            this.sizeList[scale] = 0;

            for (let ring = 0; ring < rings; ring++) {
                for (let num = 0; num < this.numberList[ring]; num++) {
                    // var alpha = num * 2 * Math.PI / n_rot_;
                    let sigma;
                    if (ring === 0) {
                        sigma = sigmaScale * this.scaleList[scale] * 0.5;
                    } else {
                        sigma = sigmaScale * this.scaleList[scale] *
                                this.radiusList[ring] * Math.sin(Math.PI / this.numberList[ring]);
                    }

                    const size = Math.ceil(this.scaleList[scale] * this.radiusList[ring] + sigma) + 1;
                    if (this.sizeList[scale] < size) {
                        this.sizeList[scale] = size;
                    }
                }
            }
        }
    }

    private createLayer(index: number, mode: number, scale: number): BRISKLayer
    {
        let below: BRISKLayer;

        if (index - 1 in this._layers) {
            below = this._layers[index - 1];
        }

        if (this._layers[index] === undefined) {
            this._layers[index] = new BRISKLayer(mode, scale, below, index);
        }

        this._layers[index].T = this._T;

        return this._layers[index];
    }
}
