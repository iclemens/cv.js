import {Observable, Observer, Operator, Subscriber, TeardownLogic} from 'rxjs';
import {Image, Keypoint} from '@iclemens/cv';
import {Split as CVSplit} from '@iclemens/cv';

export const split = (channel: number) => (source: Observable<Image>): Observable<Image> =>
    this.lift(new SplitOperator(channel));

class SplitOperator implements Operator<Image, Image>
{
    constructor(private channel: number)
    {
    }

    public call(subscriber: Subscriber<Image>, source: Observable<Image>): TeardownLogic
    {
        return source.subscribe(new SplitSubscriber(subscriber, this.channel));
    }
}


class SplitSubscriber extends Subscriber<Image>
{
    private split: CVSplit;

    constructor(destination: Subscriber<Image>, private channel: number)
    {
        super(destination);
        this.split = new CVSplit();
    }

    protected _next(value: Image): void
    {
        this.destination.next(this.split.split(value, this.channel));
    }
}
