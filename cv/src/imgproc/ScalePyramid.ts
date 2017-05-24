import {Image} from '../core/Image'
import {ImageImageData} from '../core/ImageImageData'
import {PyrDown} from './PyrDown'

export class ScalePyramid
{
    private _pyrDown: PyrDown;
    private _images: Image[] = [];
    private _scaleFactors: number[] = [];
    
    get scaleFactors(): number[] { return this._scaleFactors }
    
    constructor()
    {
        this._pyrDown = new PyrDown();
    }

    
    asPixelData(): ImageImageData[]
    {
        var result = [];
        for(var i = 0; i < this._images.length; i++) {
            result[i] = this._images[i].asImageData();
        }
        return result;
    }
    
    
    asImages(): Image[]
    {
        return this._images;
    }
    
    
    buildPyramid(input: Image, levels: number) 
    {
        // Release any old images in the pyramid
        for(var i = 0; i < this._images.length; i++) {
            if(this._images[i] === null) continue;
            this._images[i].release();
            this._images[i] = null;
        }

        // Create new pyramid, making sure copy of input image is retained
        this._images.length = levels;
        this._images[0] = input;
        this._images[0].retain();
        this._scaleFactors[0] = 1.0;

        for(var i = 1; i < levels; i++) {
            var I = this._images[i - 1];
            
            var w: number = Math.floor(0.5 * I.width);
            var h: number = Math.floor(0.5 * I.height);
            
            this._images[i] = this._pyrDown.pyrDown(I, w, h);
            this._scaleFactors[i] = this._scaleFactors[i - 1] / 2.0;
        }
    }
}