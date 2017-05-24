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
export class HaarClassifier
{
    private _haarClassifier: CV.HaarClassifier = undefined;
    private _haarClassifierShader: CV.HaarClassifierShader = undefined;
    
    
    constructor(cascade: CV.CascadeInterface)
    {
        this._haarClassifier = new CV.HaarClassifier(cascade);
        //this._haarClassifierShader = new CV.HaarClassifierShader();
    }
    
    
    Process(source: Observable<Image>): Observable<number[][]> {
        return source.map((input: Image): number[][] => {
            this._haarClassifier.setImage(input);
            var output = this._haarClassifier.detectObject();
            
            //var output = this._haarClassifierShader.detectObject(input);
            input.release();
            return output;
        });
    }
}
