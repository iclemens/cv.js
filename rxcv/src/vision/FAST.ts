import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {FAST as CVFAST} from '@iclemens/cv';

export const fast = (mask?: number, threshold?: number, S?: number, nms?: boolean, subpixel?: boolean) => 
    (source: Observable<Image>): Observable<Keypoint[]> => 
        source.lift(new FASTOperator(mask, threshold, S, nms, subpixel));

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
