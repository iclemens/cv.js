import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

export class Blur
{
    _blur: CV.Blur;
        
    constructor()
    {
        this._blur = new CV.Blur();
    }
    
    Process(source: Observable<Image>): Observable<Image>
    {        
        return source.map((input: Image) => {
            return this._blur.blur(input);
        });
    }
}
