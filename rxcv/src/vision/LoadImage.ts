import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'
import "rxjs/add/observable/defer"

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"


/**
 * Produces a sequence with a single image loaded from the specified file.
 */
export function LoadImage()
{
    this.url = "";
    
    this.CreateImage = function()
    {
        return Observable.create((observer: Observer<Image>) => {
            var img = document.createElement("img");
            var imagePool = CV.ImagePool.getInstance();

            img.onload = function() {
                var image = imagePool.getHTMLElement(img);
                observer.next(image);
                observer.complete();
            }

            img.onerror = function(err) {
                observer.error(err);
            }

            img.src = this.url;

            return function() {}  
        });        
    }
    
    this.Generate = function(source: any): Observable<Image>
    {
        if(source === undefined) {
            return Observable.defer(() => {
                return this.CreateImage();
            });
        } else {
            return source.flatMap((source: any) => {
                return this.CreateImage();
            });
        }
    }
}
