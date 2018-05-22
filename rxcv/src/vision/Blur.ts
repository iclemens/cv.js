import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Blur as CVBlur} from '@iclemens/cv';

export const blur = () => (source: Observable<Image>): Observable<Image> =>
    this.lift(new BlurOperator());

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
