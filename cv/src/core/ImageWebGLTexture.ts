import {ComputeManager} from './ComputeManager'
import {Image} from './Image'
import {ImagePool} from './ImagePool'
import {ImageImageData} from './ImageImageData'
import {ImagePoolInterface} from './ImagePool'

export class ImageWebGLTexture extends Image
{
    private _width: number = 0;
    private _height: number = 0;
    
    private _texture: WebGLTexture = null;
    private _frameBuffer: WebGLFramebuffer = null;
    
    constructor(width: number, height: number, texture: WebGLTexture = null, withFrameBuffer: boolean = false, pool: ImagePoolInterface = null)
    {
        super(pool);
        
        this._width = width;
        this._height = height;
        
        if(texture !== null) {
            this._texture = texture;
        } else {
            var computeManager = ComputeManager.getInstance();
            this._texture = computeManager.createTexture(width, height);
            
            if(withFrameBuffer)
                this._frameBuffer = computeManager.createFrameBuffer(this._texture);
        }
    }
    
    
    get width(): number
    {
        return this._width;
    }
    
    get height(): number
    {
        return this._height;
    }
    
    
    setMinFilterNearest(): void
    {
        var gl = ComputeManager.getInstance().gl();
        gl.bindTexture(gl.TEXTURE_2D, this._texture);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    }
    
    
    setMinFilterLinear(): void
    {
        var gl = ComputeManager.getInstance().gl();
        gl.bindTexture(gl.TEXTURE_2D, this._texture);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    }
    
    
    returnImage(): void
    {
        if(this._pool) {
            this._pool.returnWebGLTexture(this);
        } else {
            // Delete texture
        }
            
    }
    
    
    asImageData(): ImageImageData
    {
        var imagePool = ImagePool.getInstance();
        var cm = ComputeManager.getInstance();
        
        var output = imagePool.getImageData(this.width, this.height);
        cm.webGLTextureToImageData(this.getWebGLTexture(), output.getImageData());
        
        return output;
    }
    
    
    asWebGLTexture(): ImageWebGLTexture
    {
        this.retain();
        return this;
    }
    
    
    drawToContext2D(context: CanvasRenderingContext2D): void
    {
        var canvas = ComputeManager.getInstance().textureToCanvas(this._texture, this._width, this._height);
        context.save();
        context.translate(0, this._height);
        context.scale(1, -1);
        context.drawImage(canvas, 0, 0, this._width, this._height);
        context.restore();
    }
    
    getWebGLTexture(): WebGLTexture
    {
        return this._texture;
    }
    
    
    getWebGLFrameBuffer(): WebGLFramebuffer
    {
        return this._frameBuffer;
    }
}