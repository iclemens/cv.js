import {Filter, ShaderInfo} from '../core/Filter';
import {Image} from "../core/Image";

export class ScaleShader extends Filter
{
    protected shaders: ShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/scale.frag.c']}  
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }

    scale(image: Image, width: number, height: number): Image
    {
        if(this.programs[0] === null)
            throw "Could not apply Scaling filter, shaders have not been loaded.";
           
        var input = image.asWebGLTexture();
        var output = this.imagePool.getWebGLTexture(width, height, true);

        this.computeManager.setUniformf(this.programs[0], 'pixelSizeIn', input.getPixelSize());
        this.computeManager.setUniformf(this.programs[0], 'pixelSizeOut', output.getPixelSize());
        
        this.runShader(0, input, output);
        input.release();

        return output;
    }
}
