import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Blur as CVBlur} from '@iclemens/cv';

export function blur(this: Observable<Image>): Observable<Image> {
    return this.lift(new BlurOperator());
}

Observable.prototype.blur = blur;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      blur: typeof blur;
    }
}

class BlurOperator implements Operator<Image, Image>
{
    constructor()
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new BlurSubscriber(subscriber));
    }
}


class BlurSubscriber extends Subscriber<Image>
{
    private blur: CVBlur;

    constructor(destination: Subscriber<Image>)
    {
        super(destination);
        this.blur = new CVBlur();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.blur.blur(value));
    }
}
