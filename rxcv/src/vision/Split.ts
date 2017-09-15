/**
 * Converts a color image to grayscale.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import * as CV from '@iclemens/cv';

/**
 * Converts an RGB color image to grayscale using a normal function.
 */
export class Split
{
    private split: CV.Split;

    constructor(private channel: number)
    {
        this.split = new CV.Split();
    }


    public Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image) => {
            return this.split.split(input, this.channel);
        });
    }
}
