import {ComputeManager} from './ComputeManager';
import {Image} from './Image';
import {ImageImageData} from './ImageImageData';
import {ImagePool} from './ImagePool';
import {ImagePoolInterface} from './ImagePoolInterface';

export class ImageWebGLTexture extends Image
{
    private _width: number = 0;
    private _height: number = 0;

    private texture: WebGLTexture = null;
    private frameBuffer: WebGLFramebuffer = null;

    constructor(width: number, height: number, texture: WebGLTexture = null,
                withFrameBuffer: boolean = false, pool: ImagePoolInterface = null)
    {
        super(pool);

        this._width = width;
        this._height = height;

        if (texture !== null) {
            this.texture = texture;
        } else {
            const computeManager = ComputeManager.getInstance();
            this.texture = computeManager.createTexture(width, height);

            if (withFrameBuffer) {
                this.frameBuffer = computeManager.createFrameBuffer(this.texture);
            }
        }
    }

    get width(): number
    {
        return this._width;
    }

    get height(): number
    {
        return this._height;
    }

    public setMinFilterNearest(): void
    {
        const gl = ComputeManager.getInstance().gl();
        gl.bindTexture(gl.TEXTURE_2D, this.texture);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    }

    public setMinFilterLinear(): void
    {
        const gl = ComputeManager.getInstance().gl();
        gl.bindTexture(gl.TEXTURE_2D, this.texture);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    }

    public returnImage(): void
    {
        if (this.pool) {
            this.pool.returnWebGLTexture(this);
        } else {
            // Delete texture
        }
    }

    public asImageData(): ImageImageData
    {
        const imagePool = ImagePool.getInstance();
        const cm = ComputeManager.getInstance();

        const output = imagePool.getImageData(this.width, this.height);
        cm.webGLTextureToImageData(this.getWebGLTexture(), output.getImageData());

        return output;
    }

    public asWebGLTexture(): ImageWebGLTexture
    {
        this.retain();
        return this;
    }

    public drawToContext2D(context: CanvasRenderingContext2D): void
    {
        const canvas = ComputeManager.getInstance().textureToCanvas(this.texture, this._width, this._height);
        context.save();
        context.translate(0, this._height);
        context.scale(1, -1);
        context.drawImage(canvas, 0, 0, this._width, this._height);
        context.restore();
    }

    public getWebGLTexture(): WebGLTexture
    {
        return this.texture;
    }

    public getWebGLFrameBuffer(): WebGLFramebuffer
    {
        return this.frameBuffer;
    }
}
