import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Canny as CVCanny} from '@iclemens/cv';

export function canny(this: Observable<Image>, lowThreshold?: number, highThreshold?: number): Observable<Image> {
    return this.lift(new CannyOperator(lowThreshold, highThreshold));
}

Observable.prototype.canny = canny;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      canny: typeof canny;
    }
}

class CannyOperator implements Operator<Image, Image>
{
    constructor(private lowThreshold?: number, private highThreshold?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new CannySubscriber(subscriber, this.lowThreshold, this.highThreshold));
    }
}


class CannySubscriber extends Subscriber<Image>
{
    private canny: CVCanny;

    constructor(destination: Subscriber<Image>, private lowThreshold: number = 100, private highThreshold: number= 200)
    {
        super(destination);
        this.canny = new CVCanny();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.canny.canny(value, this.lowThreshold, this.highThreshold));
    }
}
