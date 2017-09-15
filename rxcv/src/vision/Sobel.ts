import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import * as CV from '@iclemens/cv';

export class Sobel
{
    private sobel: CV.Sobel;
    private _ksize: number = 3;

    constructor()
    {
        this.sobel = new CV.Sobel();
    }

    get ksize(): number { return this._ksize; }
    set ksize(ksize: number) { this._ksize = ksize; }

    private Process(source: Observable<Image>): Observable<Image>
    {
        return source.map((input: Image): Image => {
            return this.sobel.sobel(input, this._ksize);
        });
    }
}
