
import {Image} from "../core/Image"
import {ScaleShader} from "./ScaleShader"
import {ScaleSoftware} from "./ScaleSoftware"

interface ScaleInterface
{
    scale(image: Image, width: number, height: number)
}

export class Scale
{
    //private _scale: ScaleShader;
    private _scale: ScaleInterface;
    
    
    constructor()
    {
        this._scale = new ScaleShader();
        //this._scale = new ScaleSoftware();
    }
    
    
    scale(image: Image, widthOrScale: number, height?: number): Image
    {
        var width: number;
        
        // Determine dimensions of output image if scale is given
        if(height === undefined) {
            width = image.width * widthOrScale;
            height = image.height * widthOrScale;
        } else {
            width = widthOrScale;
        }
        
        // Make sure dimensions are positive integers
        width = Math.floor(Math.max(1, width));
        height = Math.floor(Math.max(1, height));
        
        // Do the actual scaling
        return this._scale.scale(image, width, height);
    }
}
