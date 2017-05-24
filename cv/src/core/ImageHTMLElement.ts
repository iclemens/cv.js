import {ComputeManager} from './ComputeManager'
import {Image} from './Image'
import {ImagePool} from './ImagePool'
import {ImagePoolInterface} from './ImagePool'
import {ImageWebGLTexture} from './ImageWebGLTexture'
import {ImageImageData} from './ImageImageData'

export class ImageHTMLElement extends Image
{
    private _element: HTMLVideoElement | HTMLImageElement = null;
    
    constructor(element: HTMLElement)
    {
        super(null);
        this._element = <any> element;
    }
    
    
    get width(): number
    {
        return this._element.width;  
    }
    
    get height(): number
    {
        return this._element.height;
    }
    
    asWebGLTexture(): ImageWebGLTexture
    {
        var imagePool: ImagePoolInterface = ImagePool.getInstance();
        var cm = ComputeManager.getInstance();

        var output = imagePool.getWebGLTexture(this.width, this.height, false, "ImageHTMLElements");
        cm.htmlElementToWebGLTexture(this._element, output.getWebGLTexture()); 
        
        return output;
    }
    
    
    asImageData(): ImageImageData
    {
        var cm = ComputeManager.getInstance();
        var imagePool = ImagePool.getInstance();
        var imageData = cm.imageToPixels(this._element);
        
        return new ImageImageData(imageData.width, imageData.height, imageData, null);
    }
    
    
    drawToContext2D(context: CanvasRenderingContext2D): void
    {
        context.drawImage(this._element, 0, 0, this.width, this.height);
    }
}
