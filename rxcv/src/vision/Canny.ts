import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Canny as CVCanny} from '@iclemens/cv';

export class Canny
{
    private canny: CVCanny;
    private _lowThreshold: number = 100.0;
    private _highThreshold: number = 200.0;

    constructor()
    {
        this.canny = new CVCanny();
    }

    set lowThreshold(t: number) { this._lowThreshold = t; }
    set highThreshold(t: number) { this._highThreshold = t; }

    public Process(source: Observable<Image>): Observable<Image>
    {
        return source.map((input: Image): Image => {
            return this.canny.canny(input, this._lowThreshold, this._highThreshold);
        });
    }
}
