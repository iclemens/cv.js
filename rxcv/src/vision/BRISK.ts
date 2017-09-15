import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {BRISK as CVBRISK} from '@iclemens/cv';
import {Image, Keypoint} from '@iclemens/cv';

export class BRISK
{
    private BRISK: CVBRISK;

    constructor()
    {
        this.BRISK = new CVBRISK();
    }

    get T(): number { return this.BRISK.T; }
    set T(T: number) { this.BRISK.T = T; }

    get octaveCount(): number { return this.BRISK.octaveCount; }
    set octaveCount(octaveCount: number) { this.BRISK.octaveCount = octaveCount; }

    private Process(source: Observable<Image>): Observable<Keypoint[]>
    {
        return source.map((input: Image) => {
            const features = this.BRISK.getFeatures(input);
            return features;
        });
    }
}
