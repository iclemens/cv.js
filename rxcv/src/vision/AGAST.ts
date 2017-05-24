import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

export function AGAST()
{
    var _agast = new CV.AGAST();
    
    /**
     * Default parameter values
     */
    _agast.mask = 16;
    _agast.T = 50;
    _agast.S = 9;
    _agast.nms = true;
    _agast.subpixel = false;


    /**
     * Non-maximum suppression.
     */    
    this.setNonMaxSupp = function(nms: boolean) { _agast.nms = nms; }
    
    
    /**
     * Use sub-pixel accuracy
     */
    this.setSubPixel = function(subpixel: boolean) { _agast.subpixel = subpixel; }
    
    
    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setS = function(S: number) { _agast.S = S; }
    
    
    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setMask = function(mask: number) { _agast.mask = mask; }
        
    
    /**
     * Minimum threshold score for a pixel to
     * be considered a corner. 
     */
    this.setT = function(T: number) { _agast.T = T; }

    
    this.Process = function(source: Observable<Image>): Observable<Keypoint[]> {
        return source.map(function(input: Image) {
            console.log(_agast.mask, _agast.S, _agast.T);

            var scores = _agast.getScores(input);
            return _agast.getFeatures(scores);
        });    
    }
}
