/**
 * Image.ts: Image representation.
 */
import {ComputeManager} from './ComputeManager'
import {ImagePoolInterface} from './ImagePool'

import {ImageHTMLElement} from './ImageHTMLElement'
import {ImageImageData} from './ImageImageData'
import {ImageWebGLTexture} from './ImageWebGLTexture'

export interface ImageInterface
{
    width: number
    height: number
    
    reset(): void
    
    /**
     * Increase reference counter.
     */
    retain(): void
    
    /**
     * Decrease reference counter, if
     * it reaches zero, the image will
     * be returned to the image pool.
     */
    release(): void
    
    returnImage(): void
    
    getPixelSize(): number[]
    asWebGLTexture(): ImageWebGLTexture;
    asImageData(): ImageImageData;
    
    drawToContext2D(context: CanvasRenderingContext2D): void;
}


export class Image implements ImageInterface
{
    protected _pool: ImagePoolInterface = null;
    private _refCount: number = 1;
    private _pixelSize: number[] = [0, 0];
    
    constructor(pool: ImagePoolInterface = null)
    {
        this._pool = pool;
    }
    
    reset(): void
    {
        this._refCount = 1;
    }
    
    retain(): void
    {
        this._refCount++;
    }
    
    release(): void
    {
        this._refCount--;
        
        if(this._refCount == 0 && this._pool !== null) {
            this.returnImage();
        }
    }
    
    returnImage(): void
    {        
    }
    
    get width(): number
    {
        console.warn("Could not obtain image width, not implemented", this);
        return 0.0;
    }
    
    get height(): number
    {
        console.warn("Could not obtain image height, not implemented", this);
        return 0.0;
    }
    
    getPixelSize(): number[]
    {
        this._pixelSize[0] = 1.0 / this.width;
        this._pixelSize[1] = 1.0 / this.height;
        
        return this._pixelSize;
    }
    
    asWebGLTexture(): ImageWebGLTexture
    {
        console.warn("Conversion to WebGLTexture failed, not implemented:", this);
        return null;
    }
    
    asImageData(): ImageImageData
    {
        console.warn("Conversion to ImageData failed, not implemented:", this);
        return null;
    }
    
    drawToContext2D(context: CanvasRenderingContext2D): void
    {
        console.warn("Drawing to CanvasRenderingContext2D failed, not implemented:", this);
    }
}

/*    
    asPixelData(): ImageData 
    {
        switch(this.getType()) {
            case "image":
            case "video":
                return ComputeManager.getInstance().imageToPixels(this._payload);
            case "context2d":
                var context: CanvasRenderingContext2D = this._payload.context;
                return context.getImageData(0, 0, this._width, this._height);
            case "texture":
                return ComputeManager.getInstance().textureToPixels(this._payload, this._width, this._height);
            case "imagedata":
                return <ImageData> this._payload;
            default:
                console.error("Unsupported image type (" + this.getType() + ")");
                break;
        }
    }
    
        
    asTexture(): WebGLTexture 
    {
        switch(this.getType()) {
            case "image":
            case "video":
                return ComputeManager.getInstance().imageToInputTexture(this._payload);
            case "imagedata":
                return ComputeManager.getInstance().imageDataToInputTexture(this._payload);
            case "texture":
                return this._payload;
            default:
                console.error("Unsupported image type (" + this.getType() + ")");
                break;            
        }
    }
    
    
    toContext2D(context: CanvasRenderingContext2D)
    {
        switch(this.getType()) {
            case "image":
            case "video":
                context.drawImage(this._payload, 0, 0, this._width, this._height);
                break;
            case "imagedata":
                context.putImageData(this._payload, 0, 0);
                break;
            case "texture":
                var canvas = ComputeManager.getInstance().textureToCanvas(this._payload, this._width, this._height);
                context.save();
                context.translate(0, this._height);
                context.scale(1, -1);
                context.drawImage(canvas, 0, 0, this._width, this._height);
                context.restore();
                break;
            default:
                console.error("Unsupported image type (" + this.getType() + ")");
                break;
        }              
    }
}*/
