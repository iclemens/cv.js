/**
 * Converts a color image to HSV.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {RGBToHSV as CVRGBToHSV} from '@iclemens/cv';

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class RGBToHSV
{
    private rgbToHSV: CVRGBToHSV;

    constructor()
    {
        this.rgbToHSV = new CVRGBToHSV();
    }


    public Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image): Image => {
            return this.rgbToHSV.rgbToHSV(input);
        });
    }
}
