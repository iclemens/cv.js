/**
 * Converts a color image to HSV.
 */
import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from '@iclemens/cv'

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class RGBToHSV
{
    private _rgbToHSV: CV.RGBToHSV;    
    
    constructor()
    {
        this._rgbToHSV = new CV.RGBToHSV();
    }
    
    
    Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image): Image => {
            return this._rgbToHSV.rgbToHSV(input);
        });
    }
}
