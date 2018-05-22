import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Sobel as CVSobel} from '@iclemens/cv';

export const sobel = (kSize?: number) => (source: Observable<Image>): Observable<Image> =>
    this.lift(new SobelOperator(kSize));

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
