/**
 * Converts a color image to grayscale.
 */
import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Grayscale as CVGrayscale} from '@iclemens/cv';

export const grayscale = () => (source: Observable<Image>) => 
    source.lift(new GrayscaleOperator());

class GrayscaleOperator implements Operator<Image, Image>
{
    constructor()
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new GrayscaleSubscriber(subscriber));
    }
}

class GrayscaleSubscriber extends Subscriber<Image>
{
    private grayscale: CVGrayscale;

    constructor(destination: Subscriber<Image>)
    {
        super(destination);
        this.grayscale = new CVGrayscale();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.grayscale.grayscale(value));
    }
}
