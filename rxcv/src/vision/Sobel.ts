import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {Sobel as CVSobel} from '@iclemens/cv';

export function sobel(this: Observable<Image>, kSize?: number): Observable<Image> {
    return this.lift(new SobelOperator(kSize));
}

Observable.prototype.sobel = sobel;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      sobel: typeof sobel;
    }
}

class SobelOperator implements Operator<Image, Image>
{
    constructor(private kSize?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new SobelSubscriber(subscriber, this.kSize));
    }
}


class SobelSubscriber extends Subscriber<Image>
{
    private sobel: CVSobel;

    constructor(destination: Subscriber<Image>, private kSize: number = 3)
    {
        super(destination);
        this.sobel = new CVSobel();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.sobel.sobel(value, this.kSize));
    }
}
