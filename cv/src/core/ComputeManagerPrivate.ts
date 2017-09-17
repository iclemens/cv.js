/**
 * ComputeManager.ts: Contains functions to manage WebGL resources.
 */
import {setupTexture} from './Shaders';
import {setupProgram} from './Shaders';
import {setupShaderFromFile} from './Shaders';
import {setupFramebufferWithTexture} from './Shaders';

import {IComputeManagerInterface} from './ComputeManagerInterface';


export interface IVTBuffers {
    vertex: WebGLBuffer;
    texture: WebGLBuffer;
}


export interface ICanvas2DWithContext {
    canvas: HTMLCanvasElement;
    context: CanvasRenderingContext2D;
}


export interface ICanvasGLWithContext {
    canvas: HTMLCanvasElement;
    context: WebGLRenderingContext;
}


function setupDefaultBuffers(gl: WebGLRenderingContext): IVTBuffers
{
    const vertices = new Float32Array([-1, 1, 1, 1, 1, -1, -1, 1, 1, -1, -1, -1]);
    const textureCoordinates = new Float32Array([0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
    const itemSize = 2;

    // Vertex buffer
    const vbuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vbuffer);
    gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

    // Texture coord buffer
    const tbuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, tbuffer);
    gl.bufferData(gl.ARRAY_BUFFER, textureCoordinates, gl.STATIC_DRAW);

    return {vertex: vbuffer, texture: tbuffer};
}


function attachBuffers(gl: WebGLRenderingContext, program: WebGLProgram, buffers: IVTBuffers): void
{
    gl.useProgram(program);

    // Get vertex and texture coordinate locations
    const positionLocation = gl.getAttribLocation(program, 'a_position');
    const texcoordLocation = gl.getAttribLocation(program, 'a_texcoord');

    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.vertex);
    gl.enableVertexAttribArray(positionLocation);
    gl.vertexAttribPointer(positionLocation, 2, gl.FLOAT, false, 0, 0);

    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.texture);
    gl.enableVertexAttribArray(texcoordLocation);
    gl.vertexAttribPointer(texcoordLocation, 2, gl.FLOAT, false, 0, 0);
}


/**
 * Manages WebGL contexts and textures
 */
export class ComputeManagerPrivate implements IComputeManagerInterface
{
    /**
     * Default vertex and texture buffers
     */
    protected defaultBuffers: IVTBuffers = {vertex: undefined, texture: undefined};

    /**
     * Shared canvas used for converting images to pixels.
     */
    protected sharedCanvas2D: ICanvas2DWithContext;

    /**
     * Shared canvas to perform shader operations.
     */
    protected sharedCanvasGL: ICanvasGLWithContext;

    /**
     * List of input textures.
     */
    protected inputTextures: any[] = [];

    /**
     * List of shader programs
     */
    protected shaderPrograms: {[id: string]: (WebGLProgram | Promise<WebGLProgram>)} = {};

    /**
     * Default shader program
     */
    protected defaultProgram: WebGLProgram = undefined;


    constructor()
    {
        this.sharedCanvas2D = this.createCanvas2D();
        this.sharedCanvasGL = this.createCanvasGL();

        // Create default shader program (unity operation)
        this.createShaderProgram('0b27c98f-e190-4e3d-a335-80d26f9a7c04',
            ['shaders/default.vert.c'], ['shaders/default.frag.c'])
            .then((program: WebGLProgram) => { this.defaultProgram = program; });
    }


    public createCanvas2D(): ICanvas2DWithContext
    {
        const canvas = document.createElement('canvas');
        const context = canvas.getContext('2d');

        return {canvas, context};
    }


    public createCanvasGL(): ICanvasGLWithContext
    {
        const canvas = document.createElement('canvas');
        const context = canvas.getContext('experimental-webgl');

        this.defaultBuffers = setupDefaultBuffers(context);

        return {canvas, context};
    }


    public gl(): WebGLRenderingContext
    {
        return this.sharedCanvasGL.context;
    }


    /**
     * Returns an image containing raw pixel data given an image or video element
     */
    public imageToPixels(image: HTMLImageElement | HTMLVideoElement | HTMLCanvasElement): ImageData
    {
        this.sharedCanvas2D.canvas.width = image.width;
        this.sharedCanvas2D.canvas.height = image.height;

        this.sharedCanvas2D.context.drawImage(image, 0, 0, image.width, image.height);
        return this.sharedCanvas2D.context.getImageData(0, 0, image.width, image.height);
    }


    public createTexture(width: number, height: number): WebGLTexture
    {
        return setupTexture(this.sharedCanvasGL.context, width, height);
    }


    public createFrameBuffer(texture: WebGLTexture): WebGLFramebuffer
    {
        return setupFramebufferWithTexture(this.sharedCanvasGL.context, texture);
    }


    public imageDataToWebGLTexture(imageData: ImageData, texture: WebGLTexture): void
    {
        const gl = this.sharedCanvasGL.context;
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 0);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, imageData);
    }


    /**
     * Converts an image to an input texture, which can be used
     * in the initial stage of a shader.
     */
    public htmlElementToWebGLTexture(element: HTMLElement, texture: WebGLTexture): void
    {
        const gl = this.sharedCanvasGL.context;
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 0);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, element as any);
    }


    /*imageDataToInputTexture(imageData: ImageData): WebGLTexture
    {
        // Request input texture of a given size
        var inputTexture = this.getInputTexture(imageData.width, imageData.height);

        // Upload image data to texture
        var gl = this.sharedCanvasGL.context;
        gl.bindTexture(gl.TEXTURE_2D, inputTexture);
        gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, 0);
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, imageData);

        return inputTexture;
    }*/


    public activateShader(program: WebGLProgram, width: number, height: number): void
    {
        const gl = this.sharedCanvasGL.context;
        gl.viewport(0, 0, width, height);
        gl.useProgram(program);
    }


    public setShaderInput(inputId: number, input: WebGLTexture): void
    {
        const gl = this.sharedCanvasGL.context;

        if (inputId === 0) {
            gl.activeTexture(gl.TEXTURE0);
        } else if (inputId === 1) {
            gl.activeTexture(gl.TEXTURE1);
        } else if (inputId === 2) {
            gl.activeTexture(gl.TEXTURE2);
        }

        gl.bindTexture(gl.TEXTURE_2D, input);
    }


    public setShaderOutput(output: WebGLFramebuffer): void
    {
        const gl = this.sharedCanvasGL.context;
        gl.bindFramebuffer(gl.FRAMEBUFFER, output);
    }


    public runShader(): void
    {
        const gl = this.sharedCanvasGL.context;
        gl.drawArrays(gl.TRIANGLES, 0, 6);
    }


    /**
     * Run a shader
     */
    public applyShader(input: WebGLTexture, program: WebGLProgram, output, width: number, height: number)
    {
        this.activateShader(program, width, height);
        this.setShaderInput(0, input);
        this.setShaderOutput(output['framebuffer']);
        this.runShader();
    }


    public associcateTextureUnit(program: WebGLProgram, name: string, unit: number)
    {
        this.setUniformi(program, name, unit);
    }


    public setUniform(program: WebGLProgram, name: string)
    {
        return this.sharedCanvasGL.context.getUniformLocation(program, name);
    }


    public setUniformi(program: WebGLProgram, name: string, value: number)
    {
        const gl = this.sharedCanvasGL.context;
        gl.useProgram(program);

        const location = gl.getUniformLocation(program, name);
        gl.uniform1i(location, value);
    }


    public setUniformf(program: WebGLProgram, name: string, value: (number | number[]))
    {
        const gl = this.sharedCanvasGL.context;
        gl.useProgram(program);

        const location = gl.getUniformLocation(program, name);

        if (typeof(value) === 'number') {
            gl.uniform1f(location, value);
        } else if (value.length === 2) {
            gl.uniform2f(location, value[0], value[1]);
        } else if (value.length === 3) {
            gl.uniform3f(location, value[0], value[1], value[2]);
        }
    }


    /**
     * Renders a texture to a canvas and returns the canvas.
     * The canvas should be used immediately.
     */
    public textureToCanvas(texture: WebGLTexture, width: number, height: number): HTMLCanvasElement
    {
        if (width === undefined || height === undefined || width <= 0 || height <= 0) {
            console.error('Invalid texture dimensions...');
        }

        const gl = this.sharedCanvasGL.context;
        const canvas = this.sharedCanvasGL.canvas;

        // Adjust output dimensions
        canvas.width = width;
        canvas.height = height;
        gl.viewport(0, 0, width, height);

        // Render texture to canvas
        gl.activeTexture(gl.TEXTURE0);
        gl.bindTexture(gl.TEXTURE_2D, texture);
        gl.bindFramebuffer(gl.FRAMEBUFFER, null);
        gl.useProgram(this.defaultProgram);
        gl.drawArrays(gl.TRIANGLES, 0, 6);

        // Return canvas
        return canvas;
    }


    public webGLTextureToImageData(texture: WebGLTexture, imageData: ImageData): void
    {
        const gl = this.sharedCanvasGL.context;
        const canvas = this.textureToCanvas(texture, imageData.width, imageData.height);
        const uint8Array = new Uint8Array(imageData.data.buffer);
        gl.readPixels(0, 0, imageData.width, imageData.height, gl.RGBA, gl.UNSIGNED_BYTE, uint8Array);
    }


    public createShaderProgram(id: string, vertex: string[], fragment: string[])
    {
        return new Promise((resolve: (value: WebGLProgram) => void, reject: (error: any) => void) => {

            // Check if shader was already compiled (or is being compiled)
            if (id in this.shaderPrograms) {
                if (this.shaderPrograms[id] instanceof Promise) {
                    (this.shaderPrograms[id] as Promise<WebGLProgram>).then(function() {
                        return resolve(this.shaderPrograms[id]);
                    }.bind(this));
                    return;
                } else {
                    return resolve(this.shaderPrograms[id]);
                }
            }

            this.shaderPrograms[id] = new Promise(
                (resolveInternal: (value: WebGLProgram) => void, rejectInternal: (error: any) => void) => {
                // Create new one if not
                const gl = this.sharedCanvasGL.context;

                setupProgram(gl, [
                    setupShaderFromFile(gl, 'fragment', fragment),
                    setupShaderFromFile(gl, 'vertex', vertex),
                ]).then((program: WebGLProgram) => {
                    attachBuffers(gl, program, this.defaultBuffers);

                    // Cache program and return
                    this.shaderPrograms[id] = program;
                    resolveInternal(program);
                }, rejectInternal);

            });

            (this.shaderPrograms[id] as Promise<WebGLProgram>).then(() => {
                resolve(this.shaderPrograms[id]);
            });
        });
    }
}
