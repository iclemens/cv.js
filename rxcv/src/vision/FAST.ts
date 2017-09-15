import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {FAST as CVFAST} from '@iclemens/cv';

export function FAST()
{
    const fast = new CVFAST();

    /**
     * Default parameter values
     */
    fast.mask = 16;
    fast.T = 50;
    fast.S = 9;
    fast.nms = true;
    fast.subpixel = false;


    /**
     * Non-maximum suppression.
     */
    this.setNonMaxSupp = (nms: boolean) => { fast.nms = nms; };


    /**
     * Use sub-pixel accuracy
     */
    this.setSubPixel = (subpixel: boolean) => { fast.subpixel = subpixel; };


    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setS = (S: number) => { fast.S = S; };


    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setMask = (mask: number) => { fast.mask = mask; };


    /**
     * Minimum threshold score for a pixel to
     * be considered a corner.
     */
    this.setT = (T: number) => { fast.T = T; };


    this.Process = (source: Observable<Image>): Observable<Keypoint[]> => {
        return source.map((input) => {
            const scores = fast.getScores(input);
            return fast.getFeatures(scores);
        });
    };
}
