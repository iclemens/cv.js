import {Image} from '../core/Image';
import {ImagePool} from '../core/ImagePool';

/**
 * Fallback implementation in case shaders are not present
 */
export class ScaleSoftware
{
    public scale(image: Image, width: number, height: number): Image
    {
        const imagePool = ImagePool.getInstance();

        // Convert to pixels and create output data
        const input = image.asImageData();
        const inputPixels = input.getImageData().data;
        const output = imagePool.getImageData(width, height);
        const outputPixels = output.getImageData().data;

        const lineOffset = width * 4;

        const area = (image.height / height) * (image.width / width);

        // Loop over all output pixels
        for(var y = 0; y < height; y++) {

            var y0_in = y / height * image.height;
            var y1_in = y0_in + image.height / height;

            for(var x = 0; x < width; x++) {
                const off_out = (y * width + x) * 4;
                
                // Maps to input pixels
                var x0_in = x / width * image.width;
                var x1_in = x0_in + image.width / width;
                
                var values = [0, 0, 0, 0];

                for(var dy = y0_in; dy <= y1_in && dy < image.height; dy++) {
                    var yweight = 1.0;

                    if(Math.floor(y0_in) == Math.floor(dy))
                        yweight *= 1 - (y0_in - Math.floor(y0_in));                        
                
                    if(Math.floor(y1_in) == Math.floor(dy))
                        yweight *= y1_in - Math.floor(y1_in);                        
                    
                    if(yweight == 0) continue;
                    
                    for(var dx = x0_in; dx <= x1_in && dx < image.width; dx++) {
                        var off_in = ((dy * image.width) + dx) * 4;
                        
                        var weight = yweight;
                        if(Math.floor(x0_in) == Math.floor(dx))
                            weight *= 1 - (x0_in - Math.floor(x0_in));

                        if(Math.floor(x1_in) == Math.floor(dx))
                            weight *= x1_in - Math.floor(x1_in);                            

                        if(weight == 0) continue;

                        for(var d = 0; d < 4; d++)
                            values[d] += weight * inputPixels[off_in + d];
                    }
                }
                
                for(var d = 0 ; d < 4; d++)
                    outputPixels[off_out + d] = Math.round(values[d] / area);
            }                
        }
        
        input.release();
        
        return output;
    }
}
