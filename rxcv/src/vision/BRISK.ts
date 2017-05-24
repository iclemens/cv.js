import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

export class BRISK
{    
    private _BRISK: CV.BRISK;
    
    
    constructor()
    {
        this._BRISK = new CV.BRISK();
    }
    
    
    _T: number;
    _octaveCount: number = 0;    
    
    
    get T(): number { return this._BRISK.T; }
    set T(T: number) { this._BRISK.T = T; }
    
    get octaveCount(): number { return this._BRISK.octaveCount; }
    set octaveCount(octaveCount: number) { this._BRISK.octaveCount = octaveCount; }  

    
    Process(source: Observable<Image>): Observable<Keypoint[]>
    {        
        return source.map((input: Image) => {         
            var features = this._BRISK.getFeatures(input);
            return features;
        });  
    }
}
