import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';
import {Operator} from 'rxjs/Operator';
import {Subscriber} from 'rxjs/Subscriber';
import {TeardownLogic} from 'rxjs/Subscription';

import 'rxjs/add/operator/map';

import {AGAST as CVAGAST} from '@iclemens/cv';
import {Image, Keypoint} from '@iclemens/cv';

Observable.prototype.agast = agast;

declare module 'rxjs/Observable' {
    interface Observable<T> {
      agast: typeof agast;
    }
}

export function agast(this: Observable<Image>, mask?: number, threshold?: number,
                      S?: number, nms?: boolean, subpixel?: boolean): Observable<Keypoint[]> {
    return this.lift(new AGASTOperator(mask, threshold, S, nms, subpixel));
}

class AGASTOperator implements Operator<Image, Keypoint[]>
{
    constructor(private mask?: number, private threshold?: number, private S?: number,
                private nms?: boolean, private subpixel?: boolean)
    {
    }

    public call(subscriber: Subscriber<Keypoint[]>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new AGASTSubscriber(subscriber, this.mask, this.threshold,
            this.S, this.nms, this.subpixel));
    }
}

class AGASTSubscriber extends Subscriber<Image>
{
    private agast: CVAGAST;

    constructor(destination: Subscriber<Keypoint[]>, mask: number = 16, threshold: number = 50,
                S: number = 9, nms: boolean = true, subpixel: boolean = false)
    {
        super(destination);
        this.agast = new CVAGAST();
        this.agast.mask = mask;
        this.agast.T = threshold;
        this.agast.S = S;
        this.agast.nms = nms;
        this.agast.subpixel = subpixel;
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.agast.getFeatures(this.agast.getScores(value)));
    }
}
