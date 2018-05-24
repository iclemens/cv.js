import {Observable, Observer} from 'rxjs';
import {Image, ImagePool, ImagePoolInterface, Keypoint} from '@iclemens/cv';

export interface ICameraCaptureOptions
{
    mode?: 'setInterval' | 'requestAnimationFrame';
    frequency?: number;
}


function startStreaming(observer: Observer<Image>, element: HTMLVideoElement, options: ICameraCaptureOptions): void
{
    if (!options.mode) { options.mode = 'requestAnimationFrame'; }
    if (!options.frequency) { options.frequency = 60.0; }

    const imagePool: ImagePoolInterface = ImagePool.getInstance();

    let callback: () => void;

    callback = () => {
        if (element.width === 0 || element.height === 0) {
            return;
        }

        observer.next(
            imagePool.getHTMLElement(element),
        );

        if (options.mode === 'requestAnimationFrame') {
            requestAnimationFrame(callback);
        }
    };

    if (options.mode === 'setInterval') {
        setInterval(callback, 1000.0 / options.frequency);
    } else if (options.mode === 'requestAnimationFrame') {
        requestAnimationFrame(callback);
    } else {
        observer.error('Invalid mode: ' + options.mode);
    }
}


function onStreamCallback(observer: Observer<Image>, element: HTMLVideoElement,
                          stream: MediaStream, options: ICameraCaptureOptions)
{
    element.srcObject = stream;
    element.addEventListener('playing', () => {
        // Be compatible with image element
        element.width = element.videoWidth;
        element.height = element.videoHeight;

        startStreaming(observer, element, options);
    });
    element.play();
}


/**
 * Capture video from camera.
 */
export function fromCamera(constraints: MediaStreamConstraints = { video: true },
                           options: ICameraCaptureOptions = {}): Observable<Image>
{
    return Observable.create((observer: Observer<Image>) => {
        const element: HTMLVideoElement = document.createElement('video');

        navigator.mediaDevices.getUserMedia(constraints).then(
            (stream) => onStreamCallback(observer, element, stream, options),
            (error: MediaStreamError) => {
                observer.error(error);
            });
        });
}

/**
 * Capture video from mediastream.
 */
export function fromMediaStream(stream: MediaStream,
                                options: ICameraCaptureOptions = {}): Observable<Image>
{
    return Observable.create((observer: Observer<Image>) => {
        // Create video element
        const element: HTMLVideoElement = document.createElement('video');
        onStreamCallback(observer, element, stream, options);
    });
}
