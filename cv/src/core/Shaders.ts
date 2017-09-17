import * as $ from 'jquery';
import {storedFiles} from './StoredFiles';

// Coordinates
const vertices = new Float32Array([-1, 1, 1, 1, 1, -1, -1, 1, 1, -1, -1, -1]);
const textureCoordinates = new Float32Array([0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
const itemSize = 2;


/**
 * For each shader, attach vertex and texture coordinates
 */
function setupAllShaders(gl: WebGLRenderingContext,
                         programs: Array<Promise<WebGLProgram>>): Promise<WebGLProgram[]>
{
    return new Promise((resolve, reject) => {
        Promise.all(programs).then((ps) => {
            for (const i of Object.keys(ps)) {
                const program = ps[i];

                gl.useProgram(program);

                // Get vertex and texture coordinate locations
                const positionLocation = gl.getAttribLocation(program, 'a_position');
                const texcoordLocation = gl.getAttribLocation(program, 'a_texcoord');

                // Vertex buffer
                const vbuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, vbuffer);
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                gl.enableVertexAttribArray(positionLocation);
                gl.vertexAttribPointer(positionLocation, itemSize, gl.FLOAT, false, 0, 0);

                // Texture coord buffer
                const tbuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, tbuffer);
                gl.bufferData(gl.ARRAY_BUFFER, textureCoordinates, gl.STATIC_DRAW);
                gl.enableVertexAttribArray(texcoordLocation);
                gl.vertexAttribPointer(texcoordLocation, itemSize, gl.FLOAT, false, 0, 0);
            }

            resolve(programs);
        }, (error) => {
            reject(error);
        });
    });
}

/**
 * Setup texture
 */
export function setupTexture(gl: WebGLRenderingContext, width: number, height: number): WebGLTexture
{
    const texture = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture);

    // Make sure texture coordinates are within bounds [1/2N, 1-1/2N]
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);

    // Return nearest pixel if pixel coordinates map to more than one texel
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

    // Set texture size
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, width, height, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);

    return texture;
}


/**
 * Setup framebuffer that can be used to render to a texture
 */
export function setupFramebufferWithTexture(gl, texture): WebGLFramebuffer
{
    const fb = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, fb);

    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture, 0);

    return fb;
}


/**
 * Setup program
 */
export function setupProgram(gl: WebGLRenderingContext, shaders: Array<Promise<WebGLShader>>): Promise<WebGLProgram>
{
    return new Promise((resolve, reject) => {
        Promise.all(shaders).then((shs) => {
            const program = gl.createProgram();
            for (const i of Object.keys(shs)) {
                gl.attachShader(program, shs[i]);
            }
            gl.linkProgram(program);

            if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
                reject(gl.getProgramInfoLog(program));
            }

            resolve(program);
        }, (error) => {
            reject(error);
        });
    });
}


/**
 * Sets up a shader from (string) source
 */
function setupShaderFromString(gl, type, source): Promise<WebGLShader>
{
    // Concatenate source if it's an array
    if (Array.isArray(source)) {
        source = source.join('\n');
    }

    return new Promise((resolve, reject) => {
        // Convert type-string to integer
        if (type === 'vertex') {
            type = gl.VERTEX_SHADER;
        } else if (type === 'fragment') {
            type = gl.FRAGMENT_SHADER;
        } else {
            reject('Invalid shader type, should be \'vertex\' or \'fragment\'.');
        }

        // Create and compile shader
        const reference = gl.createShader(type);
        gl.shaderSource(reference, source);
        gl.compileShader(reference);

        // Check status and return on error
        if (!gl.getShaderParameter(reference, gl.COMPILE_STATUS)) {
            const log = gl.getShaderInfoLog(reference);
            reject(log);
        }

        // Return reference
        resolve(reference);
    });
}


/**
 * Load and compile a shader from file
 */
export function setupShaderFromFile(gl, type, source: string | string[]): Promise<WebGLShader>
{
    if (!Array.isArray(source)) {
        source = [source];
    }

    const promises = [];
    for (const i in source) {
        if (source[i] in storedFiles) {
            const code = storedFiles[source[i]];
            promises.push(new Promise((resolve, reject) => {
                resolve(code);
            }));
        } else {
            promises.push($.get(source[i]));
        }
    }

    return new Promise((resolve, reject) => {
        Promise.all(promises).then((src) => {
            setupShaderFromString(gl, type, src).then((reference) => {
                resolve(reference);
            }, (error) => {
                reject(error);
            });
        }, (error) => {
            reject(error);
        });
    });
}

