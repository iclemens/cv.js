/**
 * Converts a color image to grayscale.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {CascadeInterface, HaarClassifier as CVHaarClassifier, HaarClassifierShader} from '@iclemens/cv';

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class HaarClassifier
{
    private haarClassifier: CVHaarClassifier = undefined;
    private haarClassifierShader: HaarClassifierShader = undefined;


    constructor(cascade: CascadeInterface)
    {
        this.haarClassifier = new CVHaarClassifier(cascade);
        // this._haarClassifierShader = new CV.HaarClassifierShader();
    }


    public Process(source: Observable<Image>): Observable<number[][]> {
        return source.map((input: Image): number[][] => {
            this.haarClassifier.setImage(input);
            const output = this.haarClassifier.detectObject();

            // var output = this._haarClassifierShader.detectObject(input);
            input.release();
            return output;
        });
    }
}
