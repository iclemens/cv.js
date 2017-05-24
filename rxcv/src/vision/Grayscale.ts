/**
 * Converts a color image to grayscale.
 */
import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class Grayscale
{
    private _grayscale: CV.Grayscale;    
    
    constructor()
    {
        this._grayscale = new CV.Grayscale();
    }
    
    
    Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image) => {
            return this._grayscale.grayscale(input);
        });
    }
}
