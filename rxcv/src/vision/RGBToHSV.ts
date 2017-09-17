/**
 * Converts a color image to HSV.
 */
import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import {RGBToHSV as CVRGBToHSV} from '@iclemens/cv';

export function rgbToHSV(this: Observable<Image>): Observable<Image> {
    return this.lift(new RGBToHSVOperator());
}

Observable.prototype.rgbToHSV = rgbToHSV;

declare module 'rxjs/Observable' {
    interface Observable<T> {
        rgbToHSV: typeof rgbToHSV;
    }
}

class RGBToHSVOperator implements Operator<Image, Image>
{
    constructor()
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new RGBToHSVSubscriber(subscriber));
    }
}


class RGBToHSVSubscriber extends Subscriber<Image>
{
    private rgbtohsv: CVRGBToHSV;

    constructor(destination: Subscriber<Image>)
    {
        super(destination);
        this.rgbtohsv = new CVRGBToHSV();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.rgbtohsv.rgbToHSV(value));
    }
}

