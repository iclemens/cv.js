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
import {CascadeInterface, HaarClassifier as CVHaarClassifier, HaarClassifierShader} from '@iclemens/cv';

export function haarClassifier(this: Observable<Image>, cascade: CascadeInterface): Observable<number[][]> {
    return this.lift(new HaarClassifierOperator(cascade));
}

Observable.prototype.haarClassifier = haarClassifier;

declare module 'rxjs/Observable' {
    interface Observable<T> {
        haarClassifier: typeof haarClassifier;
    }
}

class HaarClassifierOperator implements Operator<Image, number[][]>
{
    constructor(private cascade: CascadeInterface)
    {
    }

    public call(subscriber: Subscriber<number[][]>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new HaarClassifierSubscriber(subscriber, this.cascade));
    }
}


class HaarClassifierSubscriber extends Subscriber<Image>
{
    private haarClassifier: CVHaarClassifier;

    constructor(destination: Subscriber<number[][]>, cascade: CascadeInterface)
    {
        super(destination);
        this.haarClassifier = new CVHaarClassifier(cascade);
    }

    protected _next(value: Image): void
    {
        this.haarClassifier.setImage(value);
        this.destination.next(this.haarClassifier.detectObject());
        value.release();
    }
}
