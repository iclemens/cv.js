import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';


export class Sobel extends Filter
{
  protected shaders: IShaderInfo[] = [
    { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/sobel.frag.c'] },
  ];

  constructor()
  {
    super();
    this.setupShaders();
  }

  public sobel(image: Image, ksize?: number, scale?: number, delta?: number, reportMagOri?: boolean): Image
  {
    if (ksize === undefined) { ksize = 1; }
    if (scale === undefined) { scale = 1.0; }
    if (delta === undefined) { delta = 0.0; }
    if (reportMagOri === undefined) { reportMagOri = false; }

    // Make sure the parameters are correct
    if (!(ksize in [-1, 0, 1, 3, 5, 7])) {
        throw new Error('Invalid kernel size.');
    }

    const input = image.asWebGLTexture();
    this.computeManager.setUniformf(this.programs[0], 'pixelSize', image.getPixelSize());
    this.computeManager.setUniformf(this.programs[0], 'reportMagOri', reportMagOri?1.0:0.0);
    const output = this.runShader(0, input, null);
    input.release();

    return output;
  }
}
