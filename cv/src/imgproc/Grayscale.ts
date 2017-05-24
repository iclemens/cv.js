import {Image} from "../core/Image"
import {GrayscaleShader} from "./GrayscaleShader"
import {GrayscaleSoftware} from "./GrayscaleSoftware"

interface GrayscaleInterface
{
    grayscale(image: Image)
}

export class Grayscale
{
    //private _scale: ScaleShader;
    private _grayscale: GrayscaleInterface;
    
    
    constructor()
    {
        this._grayscale = new GrayscaleShader();
        //this._scale = new ScaleSoftware();
    }
    
    
    grayscale(image: Image): Image
    {
        return this._grayscale.grayscale(image);
    }
}
