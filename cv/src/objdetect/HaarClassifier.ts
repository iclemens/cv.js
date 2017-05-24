/**
 * Implementation of Viola-Jones classifier
 * 
 * Copyright (C) 2014 Ivar Clemens
 */
import {Image} from '../core/Image'
import {HaarStage} from './HaarStage'
import {IntegralImage} from './IntegralImage'
import {CascadeInterface} from './Cascade'


/**
 * Suggests the scales at which the HaarClassifier should run
 */
export function GetHaarScales(cascade: CascadeInterface, 
    imageOrWidth: Image | number, height?: number,
    scaleUpdate?: number): number[]
{
    var width = 0.0;
    if(height === undefined) {
        height = (<Image>imageOrWidth).height;
        width = (<Image>imageOrWidth).width;
    } else {
        width = <number>imageOrWidth;
    }
    
    if(scaleUpdate === undefined)
        scaleUpdate = 1.0/1.2;
    
    var scaleWidth = width / cascade.size[0];
    var scaleHeight = height / cascade.size[1];
    
    if(scaleHeight < scaleWidth)
        var scaleInitial = scaleHeight;
    else
        var scaleInitial = scaleWidth;
    
    var numIterations =  Math.ceil(Math.log(1 / scaleInitial) / Math.log(scaleUpdate));
        
    var scales = [];
    
    for(var i = 0; i < numIterations; i++) 
        scales.push(scaleInitial * Math.pow(scaleUpdate, i));
    
    return scales;        
}


/**
 * Caches some parameters that are affected by scale
 */
export interface HaarCascadeCache {
    scale: number,
    width: number,
    height: number,
    invArea: number
}


/**
 * Implements the haar classifier
 */
export class HaarClassifier
{
    private _integralImage: IntegralImage;
    private _cascade: CascadeInterface; 
    private _stages: HaarStage[];
    private _scale: number = undefined;
    private _cache: HaarCascadeCache;   
   
    get integralImage(): IntegralImage { return this._integralImage }
    get cache(): HaarCascadeCache { return this._cache }
    get width(): number { return this._cascade.size[0] }
    get height(): number { return this._cascade.size[1] }


    get scale(): number { 
        return this._scale 
    }
    
    
    set scale(s: number) {
        this._scale = Math.floor(s * 100) / 100;
        this.updateCache();
    }


    /**
     * Create new cascade, optionally specifying a scale factor
     */
    constructor(cascade: CascadeInterface, scale?: number)
    {
        this._cascade = cascade;
        this._stages = new Array(cascade.stages.length);

        this._cache = {
            scale: undefined,
            width: undefined,
            height: undefined,
            invArea: undefined	            
        }

        for(var s = 0; s < cascade.stages.length; s++) {		
            var stage = new HaarStage(this, cascade.stages[s], s);
            this._stages[s] = stage;
    	}
        
        if(scale !== undefined)
            this.scale = scale;
    }


    /**
     * Updated cached values after the scale factor changes.
     */
    private updateCache(): void
    {
        this._cache.scale = this.scale;
        this._cache.width = Math.floor(this._cascade.size[0] * this.scale);
        this._cache.height = Math.floor(this._cascade.size[1] * this.scale);
        this._cache.invArea = 1.0 / (this._cache.width * this._cache.height);
         
        // Ask stages to setScale...
        for(var s = 0; s < this._stages.length; s++) {
            this._stages[s].scale = this.scale;
        }
    }
    
    
    setImage(image: Image): void
    {
        if(this._integralImage === undefined ||
           this._integralImage.width !== image.width ||
           this._integralImage.height !== image.height) 
        {
            this._integralImage = new IntegralImage(image.width, image.height);
            
            for(var s = 0; s < this._stages.length; s++) {
                this._stages[s].integralImage = this._integralImage;
            }
        }
        
        this._integralImage.updateImage(image);
    }


    detectObject(minX?: number, maxX?: number, minY?: number, maxY?: number, stepX?: number, stepY?: number): number[][]
    {
        var result = [];

        // Fill default values if not passed
        if(minX === undefined) minX = 0.0;
        if(maxX === undefined) 
            maxX = this._integralImage.width - this._cache.width;
        else
            maxX = Math.min(maxX, this._integralImage.width - this._cache.width);
        
        if(minY === undefined) minY = 0.0;
        if(maxY === undefined) 
            maxY = this._integralImage.height - this._cache.height;
        else
            maxY = Math.min(maxY, this._integralImage.height - this._cache.height);
        
        if(stepX === undefined) {
            if(this._scale < 2) 
                stepX = Math.max(1, Math.ceil(this._scale));
            else
                stepX = 2;
        }        
        if(stepY === undefined) stepY = stepX;

        //console.log("Scale:", this._scale);

        // Loop over all pixels and apply cascade  
        var ii: IntegralImage = this._integralImage;
        var Nstages: number = this._stages.length;
        var width: number = ii.width;
      
        for(var y: number = minY; y < maxY; y += stepY) {
            for(var x: number = minX; x < maxX; x += stepX) {
                
                var offset = y * width + x;
                
                // Scaling is constant within the sub-window
                var mean = ii.getIISum(x, y, this._cache.width, this._cache.height) * this._cache.invArea;
                
                var variance =  ii.getII2Sum(x, y, this._cache.width, this._cache.height) * this._cache.invArea - (mean * mean)
                var stdev = Math.sqrt(variance);
                
                // Loop over all stages
                var i: number;
                for(i = 0; i < Nstages; i++) {
                    if(!this._stages[i].classify(ii.ii, offset, stdev, this._cache.invArea))
                        break;
                }
                
                // All stages passed, accept rectangle
                if(i == Nstages) {
                    result.push([x, y, this._cache.width, this._cache.height]);                    
                }
            }
        }		
        
        return result;   
    }
}