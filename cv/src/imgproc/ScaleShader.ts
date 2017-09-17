import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';

export class ScaleShader extends Filter
{
    protected shaders: IShaderInfo[] = [
        { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/scale.frag.c']}  
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }

    public scale(image: Image, width: number, height: number): Image
    {
        if (this.programs[0] === null) {
            throw new Error('Could not apply Scaling filter, shaders have not been loaded.');
        }

        const input = image.asWebGLTexture();
        const output = this.imagePool.getWebGLTexture(width, height, true);

        this.computeManager.setUniformf(this.programs[0], 'pixelSizeIn', input.getPixelSize());
        this.computeManager.setUniformf(this.programs[0], 'pixelSizeOut', output.getPixelSize());

        this.runShader(0, input, output);
        input.release();

        return output;
    }
}
