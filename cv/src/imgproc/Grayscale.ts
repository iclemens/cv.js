import {Image} from '../core/Image';
import {GrayscaleShader} from './GrayscaleShader';
import {GrayscaleSoftware} from './GrayscaleSoftware';

interface IGrayscaleInterface
{
    grayscale(image: Image);
}

export class Grayscale
{
    private _grayscale: IGrayscaleInterface;


    constructor()
    {
        this._grayscale = new GrayscaleShader();
        // this._scale = new ScaleSoftware();
    }


    public grayscale(image: Image): Image
    {
        return this._grayscale.grayscale(image);
    }
}
