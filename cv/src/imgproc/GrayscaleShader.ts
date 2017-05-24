import {Filter, ShaderInfo} from '../core/Filter'
import {Image} from "../core/Image"


export class GrayscaleShader extends Filter
{
    protected shaders: ShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/grayscale.frag.c'] }    
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }


    grayscale(image: Image): Image
    {
        var input = image.asWebGLTexture();
        var output = this.runShader(0, input, null);
        
        image.release();
        input.release();
        
        return output;
    }
}
