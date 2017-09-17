// Matlab compatible gradient
import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImageImageData} from '../core/ImageImageData';
import {ImagePool} from '../core/ImagePool';
import {ImagePoolInterface} from '../core/ImagePoolInterface';

export class MatGradient extends Filter
{
    protected shaders: IShaderInfo[] = [
        {
            fragmentFiles: ['shaders/gradient.frag.c'],
            vertexFiles: ['shaders/default.vert.c'],
        },
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }


    matGradient(image: Image): Image
    {
        var input = image.asWebGLTexture();
        var output = this.imagePool.getWebGLTexture(image.width, image.height, true);

        this.computeManager.setUniformf(this.programs[0], 'pixelSize', input.getPixelSize());
        
        this.runShader(0, input, output);
        input.release();

        return output;
    }
}