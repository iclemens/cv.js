import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImageImageData} from '../core/ImageImageData';
import {ImagePool} from '../core/ImagePool';
import {ImagePoolInterface} from '../core/ImagePoolInterface';

export class Split extends Filter
{
    protected shaders: IShaderInfo[] = [
        {
            fragmentFiles: ['shaders/split.frag.c'],
            vertexFiles: ['shaders/default.vert.c'],
        },
    ];


    constructor()
    {
        super();
        this.setupShaders();
    }


    public split(image: Image, channel: number): Image
    {
        const input = image.asWebGLTexture();
        const output = this.imagePool.getWebGLTexture(image.width, image.height, true);

        this.computeManager.setUniformf(this.programs[0], 'pixelSize', input.getPixelSize());
        this.computeManager.setUniformi(this.programs[0], 'channel', channel);

        this.runShader(0, input, output);
        input.release();

        return output;
    }
}
