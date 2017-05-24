import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/map'
import 'rxjs/add/operator/mergeMap'

import {Image, Keypoint} from '@iclemens/cv'
import * as CV from "@iclemens/cv"

/**
 * Capture video from camera.
 */
export class CameraCapture
{
    public startStreaming(observer: Observer<Image>, element: HTMLVideoElement)
    {
        var freq = 60.0;
        var imagePool: CV.ImagePoolInterface = CV.ImagePool.getInstance();
        
        setInterval(() => {
            if(element.width == 0 || element.height == 0) 
                return;
            
            observer.next(
                imagePool.getHTMLElement(element)
            );
        }, 1000.0/freq); 
    }

    
    /**
     * Create observable source
     */
    public Source(stream?: MediaStream, constraints?: MediaStreamConstraints): Observable<Image>
    {
        if(constraints === undefined)
            constraints = { video: true };

        return Observable.create((observer: Observer<Image>) => {
            // Create video element
            var element = document.createElement('video');

            let handleStream = (stream: MediaStream) => {
                var w = <any> window;
                
                var url: URL = w.URL || w.webkitURL;
                var src = url?(<any> url).createObjectURL(stream):stream;
                
                element.src = src;
                element.addEventListener('playing', () => {
                    // Be compatible with image element
                    element.width = element.videoWidth;
                    element.height = element.videoHeight;
                    
                    this.startStreaming(observer, element);               
                });
                element.play(); 
            };

            // Connect to source
            if(stream === undefined) {
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