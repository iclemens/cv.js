/**
 * Image.ts: Image representation.
 */
import {ComputeManager} from './ComputeManager';
import {ImagePoolInterface} from './ImagePoolInterface';

import {ImageHTMLElement} from './ImageHTMLElement';
import {ImageImageData} from './ImageImageData';
import {ImageWebGLTexture} from './ImageWebGLTexture';

export interface ImageInterface
{
    width: number;
    height: number;

    reset(): void;

    /**
     * Increase reference counter.
     */
    retain(): void;

    /**
     * Decrease reference counter, if
     * it reaches zero, the image will
     * be returned to the image pool.
     */
    release(): void;

    returnImage(): void;

    getPixelSize(): number[];
    asWebGLTexture(): ImageWebGLTexture;
    asImageData(): ImageImageData;

    drawToContext2D(context: CanvasRenderingContext2D): void;
}


export class Image implements ImageInterface
{
    private refCount: number = 1;
    private pixelSize: number[] = [0, 0];

    constructor(protected pool: ImagePoolInterface = null)
    {
    }

    public reset(): void
    {
        this.refCount = 1;
    }

    public retain(): void
    {
        this.refCount++;
    }

    public release(): void
    {
        this.refCount--;

        if (this.refCount === 0 && this.pool !== null) {
            this.returnImage();
        }
    }

    public returnImage(): void
    {
    }

    get width(): number
    {
        throw new Error('Could not obtain image width, not implemented.');
    }

    get height(): number
    {
        throw new Error('Could not obtain image height, not implemented.');
    }

    public getPixelSize(): number[]
    {
        this.pixelSize[0] = 1.0 / this.width;
        this.pixelSize[1] = 1.0 / this.height;

        return this.pixelSize;
    }

    public asWebGLTexture(): ImageWebGLTexture
    {
        throw new Error('Conversion to WebGLTexture failed, not implemented.');
    }

    public asImageData(): ImageImageData
    {
        throw new Error('Conversion to ImageData failed, not implemented.');
    }

    public drawToContext2D(context: CanvasRenderingContext2D): void
    {
        throw new Error('Drawing to CanvasRenderingContext2D failed, not implemented.');
    }
}
