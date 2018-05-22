import {Observable, Observer} from 'rxjs';

/**
 * Create an observable that returns a mediastream
 */
export function mediaStreamFromCamera(constraints: MediaStreamConstraints = { video: true }): Observable<MediaStream>
{
    return Observable.create((observer: Observer<MediaStream>) => {
        navigator.mediaDevices.getUserMedia(constraints).then(
            (stream) => { observer.next(stream); observer.complete(); },
            (error: MediaStreamError) => { observer.error(error); });
    });
}
