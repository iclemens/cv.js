import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {FAST as CVFAST} from '@iclemens/cv';


Observable.prototype.fast = fast;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      fast: typeof fast;
    }
}

export function fast(this: Observable<Image>, mask?: number, threshold?: number,
                     S?: number, nms?: boolean, subpixel?: boolean): Observable<Keypoint[]> {
    return this.lift(new FASTOperator(mask, threshold, S, nms, subpixel));
}

class FASTOperator implements Operator<Image, Keypoint[]>
{
    constructor(private mask?: number, private threshold?: number, private S?: number,
                private nms?: boolean, private subpixel?: boolean)
    {
    }

    public call(subscriber: Subscriber<Keypoint[]>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new FASTSubscriber(subscriber, this.mask, this.threshold,
            this.S, this.nms, this.subpixel));
    }
}

class FASTSubscriber extends Subscriber<Image>
{
    private fast: CVFAST;

    constructor(destination: Subscriber<Keypoint[]>, mask: number = 16, threshold: number = 50,
                S: number = 9, nms: boolean = true, subpixel: boolean = false)
    {
        super(destination);
        this.fast = new CVFAST();
        this.fast.mask = mask;
        this.fast.T = threshold;
        this.fast.S = S;
        this.fast.nms = nms;
        this.fast.subpixel = subpixel;
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.fast.getFeatures(this.fast.getScores(value)));
    }
}
