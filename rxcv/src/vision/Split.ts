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
import {Split as CVSplit} from '@iclemens/cv';


export function split(this: Observable<Image>, channel: number): Observable<Image> {
    return this.lift(new SplitOperator(channel));
}

Observable.prototype.split = split;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      split: typeof split;
    }
}

class SplitOperator implements Operator<Image, Image>
{
    constructor(private channel: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new SplitSubscriber(subscriber, this.channel));
    }
}


class SplitSubscriber extends Subscriber<Image>
{
    private split: CVSplit;

    constructor(destination: Subscriber<Image>, private channel: number)
    {
        super(destination);
        this.split = new CVSplit();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.split.split(value, this.channel));
    }
}
