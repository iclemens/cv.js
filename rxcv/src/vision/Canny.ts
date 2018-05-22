import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Canny as CVCanny} from '@iclemens/cv';

export const canny = (lowThreshold?: number, highThreshold?: number) => (source: Observable<Image>): Observable<Image> => 
    source.lift(new CannyOperator(lowThreshold, highThreshold));

class CannyOperator implements Operator<Image, Image>
{
    constructor(private lowThreshold?: number, private highThreshold?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new CannySubscriber(subscriber, this.lowThreshold, this.highThreshold));
    }
}


class CannySubscriber extends Subscriber<Image>
{
    private canny: CVCanny;

    constructor(destination: Subscriber<Image>, private lowThreshold: number = 100, private highThreshold: number= 200)
    {
        super(destination);
        this.canny = new CVCanny();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.canny.canny(value, this.lowThreshold, this.highThreshold));
    }
}
