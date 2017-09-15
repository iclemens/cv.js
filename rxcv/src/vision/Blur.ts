import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Blur as CVBlur} from '@iclemens/cv';

export class Blur
{
    private blur: CVBlur;

    constructor()
    {
        this.blur = new CVBlur();
    }

    public Process(source: Observable<Image>): Observable<Image>
    {
        return source.map((input: Image) => {
            return this.blur.blur(input);
        });
    }
}
