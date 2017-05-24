import {Image} from './Image'
import {ImageHTMLElement} from './ImageHTMLElement'
import {ImageImageData} from './ImageImageData'
import {ImageWebGLTexture} from './ImageWebGLTexture'

export interface ImagePoolInterface
{
    returnWebGLTexture(image: ImageWebGLTexture)
    returnImageData(image: ImageImageData)
    
    getHTMLElement(element: HTMLElement): ImageHTMLElement
    getWebGLTexture(width: number, height: number, withFrameBuffer: boolean, caller?: string): ImageWebGLTexture
    getImageData(width: number, height: number): ImageImageData
}

class PerformanceMonitor
{
    private _name: string;
    private _windowSize: number = 100;
    private _hits: number[];
    private _misses: number[];
    private _hit: number = 0;
    private _miss: number = 0;
    
    constructor(name: string)
    {        
        this._name = name + ':';
        this._hits = new Array(this._windowSize);   
        this._misses = new Array(this._windowSize);
        
        setInterval(function() {
            var current = this._hits[this._hit] / 1000.0;
            var first = this._hits[(this._hit + 1) % this._windowSize] / 1000.0;
            var hitRate = Math.round(this._windowSize / (current - first) * 10.0) / 10.0;
            
            current = this._misses[this._miss] / 1000.0;
            first = this._misses[(this._miss + 1) % this._windowSize] / 1000.0;
            var missRate = Math.round(this._windowSize / (current - first) * 10.0) / 10.0;
            
            //console.log('Cache Performance:',
                //this._name, hitRate, "hits/s", missRate, "misses/s");
        }.bind(this), 5000);
    }
    
    hit()
    {
        this._hit = (this._hit + 1) % this._windowSize;
        this._hits[this._hit] = Date.now();
    }
    
    miss()
    {
        this._miss = (this._miss + 1) % this._windowSize;
        this._misses[this._miss] = Date.now();
    }
}

export class ImagePoolPrivate implements ImagePoolInterface
{
    private _texturePool: ImageWebGLTexture[] = [];
    private _imageDataPool: ImageImageData[] = [];
    
    private _imageDataPerformance: PerformanceMonitor;
    private _texturePerformance: PerformanceMonitor;
    
    constructor()
    {
        this._imageDataPerformance = new PerformanceMonitor("ImageDataPool");
        this._texturePerformance = new PerformanceMonitor("TexturePool");
    }
        
    returnWebGLTexture(image: ImageWebGLTexture)
    {
        this._texturePool.push(image);
    }
    
    returnImageData(image: ImageImageData)
    {
        this._imageDataPool.push(image);
    }
    
    getHTMLElement(element: HTMLElement): ImageHTMLElement
    {
        return new ImageHTMLElement(element);
    }
    
    getWebGLTexture(width: number, height: number, withFrameBuffer: boolean = false, caller: string = ""): ImageWebGLTexture
    {
        for(var i = 0; i < this._texturePool.length; i++) {
            var candidate = this._texturePool[i];

            if(candidate.width != width || candidate.height != height)
                continue;
            
            var hasFrameBuffer = candidate.getWebGLFrameBuffer() !== null;

            if(withFrameBuffer !== hasFrameBuffer)
                continue;
            
            this._texturePerformance.hit();
            this._texturePool.splice(i, 1);
            
            candidate.reset();
            return candidate;
        }
        
        this._texturePerformance.miss();
        return new ImageWebGLTexture(width, height, null, withFrameBuffer, this);
    }
    
    getImageData(width: number, height: number): ImageImageData
    {
        for(var i = 0; i < this._imageDataPool.length; i++) {
            var candidate = this._imageDataPool[i];
            
            if(candidate.width != width || candidate.height != height)
                continue;

            this._imageDataPerformance.hit();
            this._imageDataPool.splice(i, 1);
            
            candidate.reset();
            return candidate;
        }
        
        this._imageDataPerformance.miss();
        return new ImageImageData(width, height, null, this);
    }
}

export class ImagePool 
{
    private static _instance: ImagePoolInterface = null;
    
    public static getInstance(): ImagePoolInterface
    {
        if(ImagePool._instance == null) {                
            ImagePool._instance = new ImagePoolPrivate();                
        }            
        return ImagePool._instance;
    }
}
