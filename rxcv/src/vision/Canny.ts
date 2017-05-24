import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

export class Canny
{    
    private _canny: CV.Canny;    
    private _lowThreshold: number = 100.0;
    private _highThreshold: number = 200.0;
    
    constructor()
    {
        this._canny = new CV.Canny();
    }
    
    set lowThreshold(t: number) { this._lowThreshold = t; }
    set highThreshold(t: number) { this._highThreshold = t; }

    Process(source: Observable<Image>): Observable<Image>
    {        
        return source.map((input: Image): Image => {
            return this._canny.canny(input, this._lowThreshold, this._highThreshold);
        });
    }
}
