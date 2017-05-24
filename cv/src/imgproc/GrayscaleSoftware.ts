import {Image} from "../core/Image"
import {ImageImageData} from "../core/ImageImageData"

export class GrayscaleSoftware
{
  grayscale(input: Image)
  {
    var output: ImageImageData = input.asImageData();
    var pixels: ImageData = output.getImageData();

    for(var i = 0; i < pixels.data.length; i += 4) {
        var r = pixels.data[i + 0];
        var g = pixels.data[i + 1];
        var b = pixels.data[i + 2];
        
        var gray = 0.299 * r + 0.587 * g + 0.114 * b;
        
        pixels.data[i + 0] = gray;
        pixels.data[i + 1] = gray;
        pixels.data[i + 2] = gray;
    }

    return output;   
  }  
}
