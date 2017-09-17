import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {BRISK as CVBRISK} from '@iclemens/cv';
import {Image, Keypoint} from '@iclemens/cv';

Observable.prototype.brisk = brisk;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      brisk: typeof brisk;
    }
}

export function brisk(this: Observable<Image>, threshold: number, octaveCount: number): Observable<Keypoint[]> {
    return this.lift(new BRISKOperator(threshold, octaveCount));
}

class BRISKOperator implements Operator<Image, Keypoint[]>
{
    constructor(private threshold: number, private octaveCount: number)
    {
    }

    public call(subscriber: Subscriber<Keypoint[]>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new BRISKSubscriber(subscriber, this.threshold, this.octaveCount));
    }
}

class BRISKSubscriber extends Subscriber<Image>
{
    private brisk: CVBRISK;

    constructor(destination: Subscriber<Keypoint[]>, threshold: number, octaveCount: number)
    {
        super(destination);
        this.brisk = new CVBRISK();
        this.brisk.T = threshold;
        this.brisk.octaveCount = octaveCount;
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.brisk.getFeatures(value));
    }
}
