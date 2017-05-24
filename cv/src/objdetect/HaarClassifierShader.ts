import {Filter, ShaderInfo} from '../core/Filter'
import {Image} from '../core/Image'
import {ImageImageData} from '../core/ImageImageData'
import {IntegralImage} from './IntegralImage'


/**
 * Converts a floating point array into an RGB image
 * where each float is split in three 8-bit parts.
 * 
 * If the maximum value is not given, it is assumed to
 * be the last value in the matrix.
 */
function convertImageF32I888A(pixelData: Float32Array, buffer: Uint8ClampedArray, max?: number): number
{        
    if(max === undefined)
        var max = pixelData[pixelData.length - 1];
    
    for(var i = 0; i < pixelData.length; i++) {
        var value = pixelData[i];            
        value = Math.floor(value / max * 0xFFFFFF);
                    
        buffer[i * 4 + 0] = (value & 0x0000FF);
        buffer[i * 4 + 1] = (value & 0x00FF00) >> 8;
        buffer[i * 4 + 2] = (value & 0xFF0000) >> 16;
        buffer[i * 4 + 3] = 255.0;
    }
    
    return max;
}


export class HaarClassifierShader extends Filter
{    
    private canvas: HTMLCanvasElement = undefined;
    private context: CanvasRenderingContext2D;
    
    private integralImage: IntegralImage = null;
    private iiBuffer: ImageImageData = null;
    private ii2Buffer: ImageImageData = null;
    
    protected shaders: ShaderInfo[] = [
        { 
            vertexFiles: ['shaders/default.vert.c'], 
            fragmentFiles: ['shaders/haarcascade_frontalface_alt.frag.c'], 
            inputNames: ['ii', 'ii2']
        }
    ];
    
    constructor()
    {
        super();
        this.setupShaders();
    }
    
    
    detectObject(image: Image): Image
    {        
        // Convert image to (textures with) integral images
        if(this.integralImage === null ||
           image.width != this.integralImage.width || 
           image.height != this.integralImage.height) {
               if(this.iiBuffer !== null) {
                   this.iiBuffer.release();
                   this.ii2Buffer.release();
               }
               
               this.integralImage = new IntegralImage(image.width, image.height);
               this.iiBuffer = this.imagePool.getImageData(image.width, image.height);
               this.ii2Buffer = this.imagePool.getImageData(image.width, image.height);
        }

        this.integralImage.updateImage(image);
        var iiMax = convertImageF32I888A(this.integralImage.ii, this.iiBuffer.getImageData().data);
        var ii2Max = convertImageF32I888A(this.integralImage.ii2, this.ii2Buffer.getImageData().data);
        
        var iiTexture = this.iiBuffer.asWebGLTexture();
        var ii2Texture = this.ii2Buffer.asWebGLTexture();
        
        var output = this.imagePool.getWebGLTexture(image.width, image.height, true);
        
        // Set as textures
        var cm = this.computeManager;
        cm.activateShader(this.programs[0], image.width, image.height);
        
        // Width and height are properties of the cascade
        // If "scale" changes, they change too
        // invArea = 1.0 / (20.0 * scale * 20.0 * scale);
        cm.setUniformf(this.programs[0], 'scale', 10.0);   
        
        cm.setUniformf(this.programs[0], 'iiMax', iiMax);
        cm.setUniformf(this.programs[0], 'ii2Max', ii2Max);
        cm.setUniformf(this.programs[0], 'pixelSizeIn', image.getPixelSize());
        
        // set scale, set pixelSizeIn
        cm.setShaderInput(0, iiTexture.getWebGLTexture());
        cm.setShaderInput(1, ii2Texture.getWebGLTexture());
        cm.setShaderOutput(output.getWebGLFrameBuffer());
        cm.runShader();
        
        iiTexture.release();
        ii2Texture.release();
        
        return output;
    }
}