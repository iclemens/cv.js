import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/observable/defer';
import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import * as CV from '@iclemens/cv';


/**
 * Produces a sequence with a single image loaded from the specified file.
 */
export function LoadImage()
{
    this.url = '';

    this.CreateImage = function()
    {
        return Observable.create((observer: Observer<Image>) => {
            const img = document.createElement('img');
            const imagePool = CV.ImagePool.getInstance();

            img.onload = () => {
                const image = imagePool.getHTMLElement(img);
                observer.next(image);
                observer.complete();
            };

            img.onerror = (err) => {
                observer.error(err);
            };

            img.src = this.url;

            return () => {};
        });
    };

    this.Generate = function(source: any): Observable<Image>
    {
        if (source === undefined) {
            return Observable.defer(() => {
                return this.CreateImage();
            });
        } else {
            return source.flatMap((src: any) => {
                return this.CreateImage();
            });
        }
    };
}
