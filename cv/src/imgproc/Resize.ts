/**
 * Resize
 */
import {Filter, IShaderInfo} from '../core/Filter';
import {Image} from '../core/Image';


/**
 * Resizes images
 */
export class Resize extends Filter
{
    protected shaders: IShaderInfo[] = [
        {
            fragmentFiles: ['shaders/resize.frag.c'],
            vertexFiles: ['shaders/default.vert.c'],
        },
    ];


    /**
     * Create a new instance of the resize filter. This will allocate
     * resources required to perform the resize operation.
     */
    constructor()
    {
        super();
        this.setupShaders();
    }


    /**
     * Extract the region at (xIn, yIn) with width wIn and height hIn
     * from the input image and resize it to width wOut and height hOut.
     *
     * @param image Input image
     * @param xIn X position in input image to extract
     * @param yIn Y position in input image to extract
     * @param wIn Width of region to extract from input image
     * @param hIn Height of region to extract from input image
     * @param wOut Width of the destination image
     * @param hOut Height of the destination image
     *
     * @return Cropped and resized image
     */
    public cropAndResize(image: Image,
                         xIn: number, yIn: number,
                         wIn: number, hIn: number,
                         wOut: number, hOut: number): Image
    {
        if (this.programs[0] === null) {
            throw new Error('Could not apply PyrDown filter, shaders have not been loaded.');
        }

        const input = image.asWebGLTexture();
        const output = this.imagePool.getWebGLTexture(wOut, hOut, true);

        input.setMinFilterLinear();

        this.computeManager.setUniformf(this.programs[0], 'pixelSizeIn', input.getPixelSize());
        this.computeManager.setUniformf(this.programs[0], 'pixelSizeOut', output.getPixelSize());

        this.computeManager.setUniformf(this.programs[0], 'xIn', xIn);
        this.computeManager.setUniformf(this.programs[0], 'yIn', yIn);

        this.computeManager.setUniformf(this.programs[0], 'wIn', wIn);
        this.computeManager.setUniformf(this.programs[0], 'hIn', hIn);

        this.runShader(0, input, output);

        input.setMinFilterNearest();
        input.release();

        return output;
    }


    /**
     * Resize the input image to the specified dimensions.
     *
     * @param image The image to resize.
     * @param width Width of the output image
     * @param height Height of the output image
     *
     * @return Resized image
     */
    public resize(image: Image, width: number, height: number): Image
    {
        return this.cropAndResize(image, 0, 0, image.width, image.height, width, height);
    }
}
