import {Image} from '../core/Image';
import {ImageImageData} from '../core/ImageImageData';

export class GrayscaleSoftware
{
  public grayscale(input: Image)
  {
    const output: ImageImageData = input.asImageData();
    const pixels: ImageData = output.getImageData();

    for (let i = 0; i < pixels.data.length; i += 4) {
        const r = pixels.data[i + 0];
        const g = pixels.data[i + 1];
        const b = pixels.data[i + 2];

        const gray = 0.299 * r + 0.587 * g + 0.114 * b;

        pixels.data[i + 0] = gray;
        pixels.data[i + 1] = gray;
        pixels.data[i + 2] = gray;
    }

    return output;
  }
}
