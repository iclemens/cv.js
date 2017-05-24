import {Image} from '../core/Image'
import {RGBToHSVShader} from './RGBToHSVShader'

interface RGBToHSVInterface
{
    rgbToHSV(image: Image)
}

export class RGBToHSV
{
    private _rgbToHSV: RGBToHSVInterface;
    
    
    constructor()
    {
        this._rgbToHSV = new RGBToHSVShader();
    }
    
    
    rgbToHSV(image: Image): Image
    {
        return this._rgbToHSV.rgbToHSV(image);
    }
}
