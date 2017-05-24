import {Image} from './Image'
import {ImagePool, ImagePoolInterface} from './ImagePool'
import {ImageWebGLTexture} from './ImageWebGLTexture'
import {ComputeManager} from './ComputeManager'

/**
 * Image backed by an instance of ImageData.
 */
export class ImageImageData extends Image
{
    private _imageData: ImageData;
    private _uint8Array: Uint8Array = null;
    
    constructor(width: number, height: number, imageData: ImageData = null, pool: ImagePoolInterface = null)
    {
        super(pool);
        
        if(imageData !== null) {
            this._imageData = imageData;
            
            if(width === null && height === null) 
                return;
            
            if(this._imageData.width !== width ||
               this._imageData.height !== height) {
                   throw "ImageImageData(): Payload does not match specified dimensions.";
               }
        } else {
            this._imageData = new ImageData(width, height);
        }
    }
    
    
    get width(): number
    {
        return this._imageData.width;
    }
    
    
    get height(): number
    {
        return this._imageData.height;
    }


    returnImage(): void
    {
        if(this._pool)
            this._pool.returnImageData(this);
    }


    asWebGLTexture(): ImageWebGLTexture
    {          
        var imagePool: ImagePoolInterface = ImagePool.getInstance();
        var cm = ComputeManager.getInstance();

        var output = imagePool.getWebGLTexture(this.width, this.height, false, "ImageImageData");
        cm.imageDataToWebGLTexture(this._imageData, output.getWebGLTexture());        

        return output;
    }
    
    
    getImageData(): ImageData
    {
        return this._imageData;
    }
    
    
    getUint8ClampedArray(): Uint8ClampedArray
    {
        return this._imageData.data;
    }
    
    getUint8Array(): Uint8Array
    {
        if(this._uint8Array === null)
            this._uint8Array = new Uint8Array(this._imageData.data.buffer);
        return this._uint8Array;
    }
    
    drawToContext2D(context: CanvasRenderingContext2D): void
    {
        context.putImageData(this._imageData, 0, 0);
    }
}
