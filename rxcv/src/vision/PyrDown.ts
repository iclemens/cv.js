import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {PyrDown as CVPyrDown} from '@iclemens/cv';

export const pyrDown = (scaleH?: number, scaleV?: number) => (source: Observable<Image>): Observable<Image> =>
    source.lift(new PyrDownOperator(scaleH, scaleV));

class PyrDownOperator implements Operator<Image, Image>
{
    constructor(private scaleH?: number, private scaleV?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new PyrDownSubscriber(subscriber, this.scaleH, this.scaleV));
    }
}


class PyrDownSubscriber extends Subscriber<Image>
{
    private pyrDown: CVPyrDown;

    constructor(destination: Subscriber<Image>, private scaleH: number, private scaleV?: number)
    {
        super(destination);
        this.pyrDown = new CVPyrDown();

        if (this.scaleV === undefined) {
            this.scaleV = this.scaleH;
        } else {
            this.scaleV = this.scaleV;
        }
    }

    protected _next(value: Image): void
    {
        if (this.scaleH === 0 && this.scaleV === 0) {
            this.destination.next(value);
            return;
        }

        const w = Math.floor(value.width * this.scaleV);
        const h = Math.floor(value.height * this.scaleH);

        this.destination.next(this.pyrDown.pyrDown(value, w, h));
    }
}
