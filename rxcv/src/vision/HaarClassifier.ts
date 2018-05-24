/**
 * Converts a color image to grayscale.
 */
import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {CascadeInterface, HaarClassifier as CVHaarClassifier, HaarClassifierShader} from '@iclemens/cv';

export const haarClassifier = (cascade: CascadeInterface) => (source: Observable<Image>): Observable<number[][]> =>
    source.lift(new HaarClassifierOperator(cascade));

class HaarClassifierOperator implements Operator<Image, number[][]>
{
    constructor(private cascade: CascadeInterface)
    {
    }

    public call(subscriber: Subscriber<number[][]>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new HaarClassifierSubscriber(subscriber, this.cascade));
    }
}


class HaarClassifierSubscriber extends Subscriber<Image>
{
    private haarClassifier: CVHaarClassifier;

    constructor(destination: Subscriber<number[][]>, cascade: CascadeInterface)
    {
        super(destination);
        this.haarClassifier = new CVHaarClassifier(cascade);
    }

    protected _next(value: Image): void
    {
        this.haarClassifier.setImage(value);
        this.destination.next(this.haarClassifier.detectObject());
        value.release();
    }
}
