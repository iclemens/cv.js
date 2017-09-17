import {ComputeManager} from './ComputeManager';
import {Image} from './Image';
import {ImageImageData} from './ImageImageData';
import {ImagePool} from './ImagePool';
import {ImagePoolInterface} from './ImagePoolInterface';
import {ImageWebGLTexture} from './ImageWebGLTexture';

export class ImageHTMLElement extends Image
{
    private element: HTMLVideoElement | HTMLImageElement = null;

    constructor(element: HTMLElement)
    {
        super(null);
        this.element = element as any;
    }

    get width(): number
    {
        return this.element.width;
    }

    get height(): number
    {
        return this.element.height;
    }

    public asWebGLTexture(): ImageWebGLTexture
    {
        const imagePool: ImagePoolInterface = ImagePool.getInstance();
        const cm = ComputeManager.getInstance();

        const output = imagePool.getWebGLTexture(this.width, this.height, false, 'ImageHTMLElements');
        cm.htmlElementToWebGLTexture(this.element, output.getWebGLTexture());

        return output;
    }

    public asImageData(): ImageImageData
    {
        const cm = ComputeManager.getInstance();
        const imagePool = ImagePool.getInstance();
        const imageData = cm.imageToPixels(this.element);

        return new ImageImageData(imageData.width, imageData.height, imageData, null);
    }

    public drawToContext2D(context: CanvasRenderingContext2D): void
    {
        context.drawImage(this.element, 0, 0, this.width, this.height);
    }
}
