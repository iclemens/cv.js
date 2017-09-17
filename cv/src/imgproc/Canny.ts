import {ComputeManager} from '../core/ComputeManager';
import {IComputeManagerInterface} from '../core/ComputeManagerInterface';
import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';
import {ImagePool} from '../core/ImagePool';
import {Sobel} from './Sobel';

export class Canny extends Filter
{
  protected shaders: IShaderInfo[] = [
    { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/canny.frag.c']},
    { vertexFiles: ['shaders/default.vert.c'], fragmentFiles: ['shaders/canny_hist.frag.c']}];


  constructor()
  {
    super();
    this.setupShaders();
  }


  public canny(image: Image, lowThreshold: number, highThreshold: number,
               apertureSize?: number, L2gradient?: boolean): Image
  {
    if (this.programs[0] === null || this.programs[1] === null) {
      throw new Error('Could not apply Canny filter, shaders have not been loaded.');
    }

    if (apertureSize === undefined) {
      apertureSize = 1;
    }

    if (L2gradient === undefined) {
      L2gradient = true;
    }

    // Make sure the parameters are correct
    if (!(apertureSize in [-1, 0, 1, 3, 5, 7])) {
      throw new Error('Invalid aperature size.');
    }

    if (lowThreshold > highThreshold) {
      const tmp = highThreshold;
      highThreshold = lowThreshold;
      lowThreshold = tmp;
    }

    const texture = image.asWebGLTexture();

    const imagePool = ImagePool.getInstance();
    const output0 = imagePool.getWebGLTexture(image.width, image.height, true);
    const output1 = imagePool.getWebGLTexture(image.width, image.height, true);

    this.computeManager.activateShader(this.programs[0], image.width, image.height);
    this.computeManager.setShaderInput(0, texture.getWebGLTexture());
    this.computeManager.setShaderOutput(output0.getWebGLFrameBuffer());
    this.computeManager.setUniformf(this.programs[0], 'pixelSize', image.getPixelSize());
    this.computeManager.setUniformf(this.programs[0], 'lowThreshold', lowThreshold / 255.0);
    this.computeManager.setUniformf(this.programs[0], 'highThreshold', highThreshold / 255.0);
    this.computeManager.setUniformf(this.programs[0], 'L2gradient', 0.0);
    this.computeManager.runShader();
    texture.release();

    this.computeManager.activateShader(this.programs[0], image.width, image.height);
    this.computeManager.setShaderInput(0, output0.getWebGLTexture());
    this.computeManager.setShaderOutput(output1.getWebGLFrameBuffer());
    this.computeManager.setUniformf(this.programs[1], 'pixelSize', image.getPixelSize());
    this.computeManager.runShader();
    output0.release();

    return output1;
  }
}
