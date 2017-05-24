import {Filter, ShaderInfo} from '../core/Filter'
import {Image} from '../core/Image'
import {ImageImageData} from '../core/ImageImageData'
import {ImagePool, ImagePoolInterface} from '../core/ImagePool'

export class Split extends Filter
{
    protected shaders: ShaderInfo[] = [
        { 
            vertexFiles: ['shaders/default.vert.c'], 
            fragmentFiles: ['shaders/split.frag.c']
        }
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }
    
    
    split(image: Image, channel: number): Image
    {
        var input = image.asWebGLTexture();
        var output = this.imagePool.getWebGLTexture(image.width, image.height, true);

        this.computeManager.setUniformf(this.programs[0], 'pixelSize', input.getPixelSize());
        this.computeManager.setUniformi(this.programs[0], 'channel', channel);
        
        this.runShader(0, input, output);
        input.release();

        return output;
    }
}