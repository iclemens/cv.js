import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {BRISK as CVBRISK} from '@iclemens/cv';
import {Image, Keypoint} from '@iclemens/cv';

export const brisk = (threshold: number, octaveCount: number) => (source: Observable<Image>): Observable<Keypoint[]> =>
    source.lift(new BRISKOperator(threshold, octaveCount));

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
