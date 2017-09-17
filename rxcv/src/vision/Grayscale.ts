/**
 * Converts a color image to grayscale.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Grayscale as CVGrayscale} from '@iclemens/cv';

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class Grayscale
{
    private grayscale: CVGrayscale;

    constructor()
    {
        this.grayscale = new CVGrayscale();
    }


    public Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image) => {
            return this.grayscale.grayscale(input);
        });
    }
}
