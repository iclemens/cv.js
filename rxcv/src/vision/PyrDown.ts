import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {PyrDown as CVPyrDown} from '@iclemens/cv';

export function pyrDown(this: Observable<Image>, scaleH?: number, scaleV?: number): Observable<Image> {
    return this.lift(new PyrDownOperator(scaleH, scaleV));
}

Observable.prototype.pyrDown = pyrDown;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      pyrDown: typeof pyrDown;
    }
}

class PyrDownOperator implements Operator<Image, Image>
{
    constructor(private scaleH?: number, private scaleV?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new PyrDownSubscriber(subscriber, this.scaleH, this.scaleV));
    }
}


class PyrDownSubscriber extends Subscriber<Image>
{
    private pyrDown: CVPyrDown;

    constructor(destination: Subscriber<Image>, private scaleH: number, private scaleV?: number)
    {
        super(destination);
        this.pyrDown = new CVPyrDown();

        if (this.scaleV === undefined) {
            this.scaleV = this.scaleH;
        } else {
            this.scaleV = this.scaleV;
        }
    }

    protected _next(value: Image): void
    {
        if (this.scaleH === 0 && this.scaleV === 0) {
            this.destination.next(value);
            return;
        }

        const w = Math.floor(value.width * this.scaleV);
        const h = Math.floor(value.height * this.scaleH);

        this.destination.next(this.pyrDown.pyrDown(value, w, h));
    }
}
