import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';
import 'rxjs/add/operator/mergeMap';

import {Image, ImagePool, ImagePoolInterface, Keypoint} from '@iclemens/cv';

/**
 * Capture video from camera.
 */
export class CameraCapture
{
    public startStreaming(observer: Observer<Image>, element: HTMLVideoElement): void
    {
        const freq = 60.0;
        const imagePool: ImagePoolInterface = ImagePool.getInstance();

        setInterval(() => {
            if (element.width === 0 || element.height === 0) {
                return;
            }

            observer.next(
                imagePool.getHTMLElement(element),
            );
        }, 1000.0 / freq);
    }


    /**
     * Create observable source
     */
    public Source(stream?: MediaStream, constraints?: MediaStreamConstraints): Observable<Image>
    {
        if (constraints === undefined) {
            constraints = { video: true };
        }

        return Observable.create((observer: Observer<Image>) => {
            // Create video element
            const element = document.createElement('video');

            const handleStream = (str: MediaStream) => {
                const w = window as any;

                // const url: URL = w.URL || w.webkitURL;
                // const src = url?(<any> url).createObjectURL(stream):stream;
                // element.src = src;

                element.srcObject = str;
                element.addEventListener('playing', () => {
                    // Be compatible with image element
                    element.width = element.videoWidth;
                    element.height = element.videoHeight;

                    this.startStreaming(observer, element);
                });
                element.play();
            };

            // Connect to source
            if (stream === undefined) {
                navigator.mediaDevices.getUserMedia(constraints).then(
                    handleStream.bind(this),
                    (error: MediaStreamError) => {
                        observer.error(error);
                    });
            } else {
                handleStream(stream);
            }
        });
    }


    /**
     * Takes an observable that produces streams and returns
     *  an observable that produces frames from those streams.
     */
    public Process(source: Observable<MediaStream>): Observable<Image>
    {
        return source.mergeMap((stream) => {
            return this.Source(stream);
        });
    }
}
