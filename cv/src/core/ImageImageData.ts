import {ComputeManager} from './ComputeManager';
import {Image} from './Image';
import {ImagePool} from './ImagePool';
import {ImagePoolInterface} from './ImagePoolInterface';
import {ImageWebGLTexture} from './ImageWebGLTexture';

/**
 * Image backed by an instance of ImageData.
 */
export class ImageImageData extends Image
{
    private imageData: ImageData;
    private uint8Array: Uint8Array = null;

    constructor(width: number, height: number, imageData: ImageData = null, pool: ImagePoolInterface = null)
    {
        super(pool);

        if (imageData !== null) {
            this.imageData = imageData;

            if (width === null && height === null) {
                return;
            }

            if (this.imageData.width !== width ||
                this.imageData.height !== height) {
                   throw new Error('ImageImageData(): Payload does not match specified dimensions.');
               }
        } else {
            this.imageData = new ImageData(width, height);
        }
    }

    get width(): number
    {
        return this.imageData.width;
    }

    get height(): number
    {
        return this.imageData.height;
    }

    /**
     * Returns the image to the pool.
     */
    public returnImage(): void
    {
        if (this.pool) {
            this.pool.returnImageData(this);
        }
    }

    /**
     * Convert the image into a WebGL texture.
     */
    public asWebGLTexture(): ImageWebGLTexture
    {
        const imagePool: ImagePoolInterface = ImagePool.getInstance();
        const cm = ComputeManager.getInstance();

        const output = imagePool.getWebGLTexture(this.width, this.height, false, 'ImageImageData');
        cm.imageDataToWebGLTexture(this.imageData, output.getWebGLTexture());

        return output;
    }

    public getImageData(): ImageData
    {
        return this.imageData;
    }

    public getUint8ClampedArray(): Uint8ClampedArray
    {
        return this.imageData.data;
    }

    public getUint8Array(): Uint8Array
    {
        if (this.uint8Array === null) {
            this.uint8Array = new Uint8Array(this.imageData.data.buffer);
        }
        return this.uint8Array;
    }

    /**
     * Draw the image onto a 2d canvas.
     */
    public drawToContext2D(context: CanvasRenderingContext2D): void
    {
        context.putImageData(this.imageData, 0, 0);
    }
}
