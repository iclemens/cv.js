import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';


export class RGBToHSVShader extends Filter
{
    protected shaders: IShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/rgbtohsv.frag.c'] },
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }


    public rgbToHSV(image: Image): Image
    {
        const input = image.asWebGLTexture();
        const output = this.runShader(0, input, null);

        image.release();
        input.release();

        return output;
    }
}
