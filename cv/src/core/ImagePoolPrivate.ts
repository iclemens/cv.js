import {Image} from './Image';
import {ImageHTMLElement} from './ImageHTMLElement';
import {ImageImageData} from './ImageImageData';
import {ImageWebGLTexture} from './ImageWebGLTexture';

import {ImagePoolInterface} from './ImagePoolInterface';
import {PerformanceMonitor} from './PerformanceMonitor';

export class ImagePoolPrivate implements ImagePoolInterface
{
    private texturePool: ImageWebGLTexture[] = [];
    private imageDataPool: ImageImageData[] = [];

    private imageDataPerformance: PerformanceMonitor;
    private texturePerformance: PerformanceMonitor;

    constructor()
    {
        this.imageDataPerformance = new PerformanceMonitor('ImageDataPool');
        this.texturePerformance = new PerformanceMonitor('TexturePool');
    }

    public returnWebGLTexture(image: ImageWebGLTexture)
    {
        this.texturePool.push(image);
    }

    public returnImageData(image: ImageImageData)
    {
        this.imageDataPool.push(image);
    }

    public getHTMLElement(element: HTMLElement): ImageHTMLElement
    {
        return new ImageHTMLElement(element);
    }

    public getWebGLTexture(width: number, height: number,
                           withFrameBuffer: boolean = false, caller: string = ''): ImageWebGLTexture
    {
        for (let i = 0; i < this.texturePool.length; i++) {
            const candidate = this.texturePool[i];

            if (candidate.width !== width || candidate.height !== height) {
                continue;
            }

            const hasFrameBuffer = candidate.getWebGLFrameBuffer() !== null;

            if (withFrameBuffer !== hasFrameBuffer) {
                continue;
            }

            this.texturePerformance.hit();
            this.texturePool.splice(i, 1);

            candidate.reset();
            return candidate;
        }

        this.texturePerformance.miss();
        return new ImageWebGLTexture(width, height, null, withFrameBuffer, this);
    }

    public getImageData(width: number, height: number): ImageImageData
    {
        for (let i = 0; i < this.imageDataPool.length; i++) {
            const candidate = this.imageDataPool[i];

            if (candidate.width !== width || candidate.height !== height) {
                continue;
            }

            this.imageDataPerformance.hit();
            this.imageDataPool.splice(i, 1);

            candidate.reset();
            return candidate;
        }

        this.imageDataPerformance.miss();
        return new ImageImageData(width, height, null, this);
    }
}
