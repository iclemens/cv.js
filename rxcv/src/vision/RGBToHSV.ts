/**
 * Converts a color image to HSV.
 */
import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {RGBToHSV as CVRGBToHSV} from '@iclemens/cv';

export const rgbToHSV = () => (source: Observable<Image>): Observable<Image> => 
    this.lift(new RGBToHSVOperator());

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

