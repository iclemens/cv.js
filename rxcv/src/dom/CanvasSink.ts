import {Observable} from 'rxjs/Observable'
import {Observer} from 'rxjs/Observer'

import 'rxjs/add/operator/do'

import {Image} from '@iclemens/cv'

/**
 * Sink that renders an image onto a canvas.
 */
export class CanvasSink
{
    public element: HTMLCanvasElement = undefined;
    private context2D: CanvasRenderingContext2D = undefined;
    
    constructor()
    {
    }
    
    public Process(source: Observable<Image>): any
    {
        this.context2D = this.element.getContext("2d");
        
        return Observable.create((observer: Observer<Image>) => {
            var process = source.do((image: Image) => {
                if(this.element === undefined)
                    return;

                if(this.element.width != image.width || this.element.height != image.height) {
                    this.element.width = image.width;
                    this.element.height = image.height;
                }

                image.drawToContext2D(this.context2D);
                image.release();
            }).subscribe(observer);
            
            return function() { }
        });
    }
}