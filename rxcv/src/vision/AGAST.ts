import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {AGAST as CVAGAST} from '@iclemens/cv';
import {Image, Keypoint} from '@iclemens/cv';

export function AGAST()
{
    const agast = new CVAGAST();

    /**
     * Default parameter values
     */
    agast.mask = 16;
    agast.T = 50;
    agast.S = 9;
    agast.nms = true;
    agast.subpixel = false;


    /**
     * Non-maximum suppression.
     */
    this.setNonMaxSupp = (nms: boolean) => { agast.nms = nms; };


    /**
     * Use sub-pixel accuracy
     */
    this.setSubPixel = (subpixel: boolean) => { agast.subpixel = subpixel; };


    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setS = (S: number) => { agast.S = S; };


    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setMask = (mask: number) => { agast.mask = mask; };


    /**
     * Minimum threshold score for a pixel to
     * be considered a corner.
     */
    this.setT = (T: number) => { agast.T = T; };


    this.Process = (source: Observable<Image>): Observable<Keypoint[]> => {
        return source.map((input: Image) => {
            const scores = agast.getScores(input);
            return agast.getFeatures(scores);
        });
    };
}
