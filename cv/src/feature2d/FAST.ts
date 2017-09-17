import {ComputeManager} from '../core/ComputeManager';
import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImagePool} from '../core/ImagePool';
import {Keypoint} from '../core/Keypoint';

export class FAST extends Filter
{
    protected shaders: IShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/lib/fast.frag.c', 'shaders/fast.frag.c']},
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/fast_filter.frag.c']},
    ];

    // FAST parameters
    private _T: number = 50;
    private _S: number = 9;
    private _mask: number = 16;
    private _nms: boolean = false;
    private _subpixel: boolean = false;


    constructor() {
        super();
        this.setupShaders();
    }


    // Getter and setter functions
    get T(): number { return this._T; }
    set T(T: number) { this._T = T; }

    get S(): number { return this._S; }
    set S(S: number) { this._S = S; }

    get mask(): number { return this._mask; }
    set mask(mask: number) { this._mask = mask; }

    get nms(): boolean { return this._nms; }
    set nms(nms: boolean) { this._nms = nms; }

    get subpixel(): boolean { return this._subpixel; }
    set subpixel(subpixel: boolean) { this._subpixel = subpixel; }


    public getScores(input: Image): Image {
        if (this.programs[0] === null || this.programs[1] === null) {
            throw new Error('Could not apply FAST filter, shaders have not been loaded.');
        }

        // Convert input to texture
        const texture = input.asWebGLTexture();

        const imagePool = ImagePool.getInstance();
        const output0 = imagePool.getWebGLTexture(input.width, input.height, true);
        const output1 = imagePool.getWebGLTexture(input.width, input.height, true);

        // Run FAST shader
        this.computeManager.activateShader(this.programs[0], input.width, input.height);
        this.computeManager.setShaderInput(0, texture.getWebGLTexture());
        this.computeManager.setShaderOutput(output0.getWebGLFrameBuffer());
        this.computeManager.setUniformi(this.programs[0], 'S', this._S);
        this.computeManager.setUniformi(this.programs[0], 'mask', this._mask);
        this.computeManager.setUniformf(this.programs[0], 'pixelSize', input.getPixelSize());
        this.computeManager.setUniformf(this.programs[0], 'T', this._T / 256.0);
        this.computeManager.runShader();
        texture.release();

        // If we don't want to run NMS, return here
        if (!this._nms) {
            return output0;
        }

        // Run NMS shader
        this.computeManager.activateShader(this.programs[1], input.width, input.height);
        this.computeManager.setShaderInput(0, output0.getWebGLTexture());
        this.computeManager.setShaderOutput(output1.getWebGLFrameBuffer());
        this.computeManager.setUniformi(this.programs[1], 'subPixel', this._subpixel ? 1 : 0);
        this.computeManager.setUniformf(this.programs[1], 'pixelSize', input.getPixelSize());
        this.computeManager.setUniformf(this.programs[1], 'T', this._T / 256.0);
        this.computeManager.runShader();
        output0.release();

        return output1;
    }


    public getFeatures(scores: Image): Keypoint[] {
        const features = [];
        const scoresImageData = scores.asImageData();
        const pixels = scoresImageData.getImageData();

        for (let y = 0; y < scores.height; y++) {
            for (let x = 0; x < scores.width; x++) {
                const offset: number = (x + scores.width * y) * 4;

                if (pixels.data[offset] < this._T) { continue; }

                features.push({
                    score: pixels.data[offset + 0],
                    x,
                    xoffset: pixels.data[offset + 1] / 256.0 * 6.0 - 3.0,
                    y,
                    yoffset: pixels.data[offset + 2] / 256.0 * 6.0 - 3.0,
                });
            }
        }

        scoresImageData.release();

        return features;
    }
}
