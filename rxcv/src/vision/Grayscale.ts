/**
 * Converts a color image to grayscale.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Grayscale as CVGrayscale} from '@iclemens/cv';


export function grayscale(this: Observable<Image>): Observable<Image> {
    return this.lift(new GrayscaleOperator());
}

Observable.prototype.grayscale = grayscale;

declare module 'rxjs/Observable' {
    interface Observable<T> {
        grayscale: typeof grayscale;
    }
}

class GrayscaleOperator implements Operator<Image, Image>
{
    constructor()
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new GrayscaleSubscriber(subscriber));
    }
}


class GrayscaleSubscriber extends Subscriber<Image>
{
    private grayscale: CVGrayscale;

    constructor(destination: Subscriber<Image>)
    {
        super(destination);
        this.grayscale = new CVGrayscale();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.grayscale.grayscale(value));
    }
}
