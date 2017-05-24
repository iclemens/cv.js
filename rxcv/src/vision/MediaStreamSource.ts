import * as CV from "@iclemens/cv"
import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

/**
 * Source that produces a mediastream once subscribed to.
 */
export class MediaStreamSource
{
    /**
     * Create observable source
     */
    public Source(stream?: MediaStream, constraints?: MediaStreamConstraints): Observable<MediaStream>
    {
        if(constraints === undefined)
            constraints = { video: true };

        if(stream === undefined) {
            return Observable.create((observer: Observer<MediaStream>) => {
                navigator.mediaDevices.getUserMedia(constraints).then( 
                    (stream: MediaStream) => {
                        observer.next(stream);
                    }, (error: MediaStreamError) => {
                        observer.error(error);
                    });
            });
        } else {
            return Observable.create((observer: Observer<MediaStream>) => {
                observer.next(stream);
            });
        }
    } 
}