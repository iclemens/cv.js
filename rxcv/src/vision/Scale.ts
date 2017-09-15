import {Observable} from 'rxjs/Observable';
import {Observer} from 'rxjs/Observer';

import 'rxjs/add/operator/map';

import {Image, Keypoint} from '@iclemens/cv';
import * as CV from '@iclemens/cv';

export class Scale
{
    private _scale: CV.Scale;
    private _scaleH: number;
    private _scaleV: number;

    constructor()
    {
        this._scale = new CV.Scale();
    }

    get scaleH(): number { return this._scaleH; }
    set scaleH(scaleH: number) { this._scaleH = scaleH; }

    get scaleV(): number { return this._scaleV; }
    set scaleV(scaleV: number) { this._scaleV = scaleV; }

    public setScale(scaleH: number, scaleV?: number): void
    {
        this.scaleH = scaleH;

        if (scaleV === undefined) {
            this.scaleV = scaleH;
        } else {
            this.scaleV = scaleV;
        }
    }

    public Process(source: Observable<Image>): Observable<Image>
    {
        return source.map((input: Image) => {
            if (this.scaleH === 1.0 && this.scaleV === 1.0) {
                return input;
            }

            // Width/height
            const w = Math.floor(input.width * this._scaleH);
            const h = Math.floor(input.height * this._scaleH);

            return this._scale.scale(input, w, h);
        });
    }
}
