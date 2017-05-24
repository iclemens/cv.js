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
export class Split
{
    private _split: CV.Split;    
    private _channel: number;
    
    constructor(channel: number)
    {
        this._split = new CV.Split();
        this._channel = channel;
    }
    
    
    Process(source: Observable<Image>): Observable<Image> {
        return source.map((input: Image) => {
            return this._split.split(input, this._channel);
        });
    }
}
