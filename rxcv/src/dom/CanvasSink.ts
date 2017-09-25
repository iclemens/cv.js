import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Subscriber} from 'rxjs/Subscriber';

import 'rxjs/add/operator/do';

import {Image} from '@iclemens/cv';

/**
 * Sink that renders an image onto a canvas.
 */
export class CanvasSink extends Subscriber<Image>
{
    private context2D: CanvasRenderingContext2D = undefined;

    constructor(public element: HTMLCanvasElement,
                private afterUpdate?: (image: Image, context: CanvasRenderingContext2D) => void)
    {
        super();
        this.context2D = this.element.getContext('2d');
    }

    protected _next(image: Image)
    {
        if (this.element === undefined) {
            return;
        }

        if (this.element.width !== image.width || this.element.height !== image.height) {
            this.element.width = image.width;
            this.element.height = image.height;
        }

        image.drawToContext2D(this.context2D);

        if (this.afterUpdate) {
            this.afterUpdate(image, this.context2D);
        }

        image.release();
    }
}
