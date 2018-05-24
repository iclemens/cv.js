import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Scale as CVScale} from '@iclemens/cv';

export const scale = (scaleH?: number, scaleV?: number) => (source: Observable<Image>): Observable<Image> => 
    source.lift(new ScaleOperator(scaleH, scaleV));

class ScaleOperator implements Operator<Image, Image>
{
    constructor(private scaleH?: number, private scaleV?: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new ScaleSubscriber(subscriber, this.scaleH, this.scaleV));
    }
}


class ScaleSubscriber extends Subscriber<Image>
{
    private scale: CVScale;

    constructor(destination: Subscriber<Image>, private scaleH: number, private scaleV?: number)
    {
        super(destination);
        this.scale = new CVScale();

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

        this.destination.next(this.scale.scale(value, w, h));
    }
}

