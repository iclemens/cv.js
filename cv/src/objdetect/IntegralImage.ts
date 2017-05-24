/**
 * Implementation of Viola-Jones classifier
 * 
 * Copyright (C) 2014 Ivar Clemens
 */

import {Image} from "../core/Image"

export class IntegralImage
{
    private _width: number;
    private _height: number;
    
    
    public ii: Float32Array;
    public ii2: Float32Array;
    
    
    get width(): number { return this._width; }
    get height(): number { return this._height; }
    

    constructor(width: number, height: number)
    {
        this._width = width + 1;
        this._height = height + 1;
        
        this.ii = new Float32Array(this._width * this._height);
        this.ii2 = new Float32Array(this._width * this._height);
    }
    
    
    updateImage(image: Image)
    {
        var input = image.asImageData();
        var imageData: ImageData = input.getImageData();
        
        var w = imageData.width + 1;
        var h = imageData.height + 1;
 
        if(w != this._width || h != this._height)
            throw "IntegralImage: Invalid image dimensions.";
        
        for(var x = 1; x < w; x++) {
            for(var y = 1; y < h; y++) {
                var idxII = y * w + x;
                var idxIm = (y - 1) * imageData.width + (x - 1);
                	
                var value = imageData.data[idxIm * 4] / 255;
                
                this.ii[idxII] = value + this.ii[idxII - 1] + this.ii[idxII - w] - this.ii[idxII - w - 1];
                this.ii2[idxII] = value * value + this.ii2[idxII - 1] + this.ii2[idxII - w] - this.ii2[idxII - w - 1];
            }
        }
        
        input.release();
    }
    
    getIISum(x: number, y: number, w: number, h: number): number
    {
        var top_left = y * this.width + x;
        var bottom_left = (y + h) * this.width + x;
        
        return this.ii[bottom_left + w] + this.ii[top_left] - this.ii[top_left + w] - this.ii[bottom_left];	
    }
    
    getII2Sum(x: number, y: number, w: number, h: number): number
    {
        var top_left = y * this.width + x;
        var top_right = top_left + w;
        var bottom_left = (y + h) * this.width + x;
        var bottom_right = bottom_left + w;
        
        return this.ii2[bottom_right] + this.ii2[top_left] - this.ii2[top_right] - this.ii2[bottom_left];
    }
}
