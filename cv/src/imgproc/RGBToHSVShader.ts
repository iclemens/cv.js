import {Filter, ShaderInfo} from '../core/Filter'
import {Image} from '../core/Image'


export class RGBToHSVShader extends Filter
{
    protected shaders: ShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/rgbtohsv.frag.c'] }    
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }


    rgbToHSV(image: Image): Image
    {
        var input = image.asWebGLTexture();
        var output = this.runShader(0, input, null);
        
        image.release();
        input.release();
        
        return output;
    }
}
