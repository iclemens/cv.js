import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImagePool} from '../core/ImagePool';

export class Blur extends Filter
{
    protected shaders: IShaderInfo[] = [
        {
            fragmentFiles: ['shaders/blur.frag.c'],
            vertexFiles: ['shaders/default.vert.c'],
        },
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }
    
    
    /**
     * Applies Gaussian blur (3x3 kernel) to the image
     * @param image   Image to blur
     * @returns       Blurred image
     */
    blur(image: Image): Image
    {
        var imagePool = ImagePool.getInstance();
        
        var inputTexture = image.asWebGLTexture();
        var outputTexture = imagePool.getWebGLTexture(image.width, image.height, true);
        
        // Blur image
        this.computeManager.activateShader(this.programs[0], image.width, image.height);
        this.computeManager.setShaderInput(0, inputTexture.getWebGLTexture());
        this.computeManager.setShaderOutput(outputTexture.getWebGLFrameBuffer());
        this.computeManager.setUniformf(this.programs[0], 'pixelSize', image.getPixelSize());
        this.computeManager.runShader();
        
        inputTexture.release();
        
        return outputTexture;           
    }
}