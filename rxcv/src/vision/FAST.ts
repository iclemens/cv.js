import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

export function FAST()
{
    var _fast = new CV.FAST();
    
    /**
     * Default parameter values
     */
    _fast.mask = 16;
    _fast.T = 50;
    _fast.S = 9;
    _fast.nms = true;
    _fast.subpixel = false;
        
    
    /**
     * Non-maximum suppression.
     */    
    this.setNonMaxSupp = function(nms: boolean) { _fast.nms = nms; }
    
    
    /**
     * Use sub-pixel accuracy
     */
    this.setSubPixel = function(subpixel: boolean) { _fast.subpixel = subpixel; }
    
    
    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setS = function(S: number) { _fast.S = S; }
    
    
    /**
     * Size of segment above/below threshold for
     * a pixel to be considered a corner.
     */
    this.setMask = function(mask: number) { _fast.mask = mask; }
        
    
    /**
     * Minimum threshold score for a pixel to
     * be considered a corner. 
     */
    this.setT = function(T: number) { _fast.T = T; }
    
    
    this.Process = function(source: Observable<Image>): Observable<Keypoint[]> {         
        return source.map((input) => {            
            var scores = _fast.getScores(input);           
            return _fast.getFeatures(scores);
        });
    }
}
