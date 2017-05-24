import {storedFiles} from './StoredFiles';
import * as $ from 'jquery';

// Coordinates
var vertices = new Float32Array([-1, 1, 1, 1, 1, -1, -1, 1, 1, -1, -1, -1]);
var textureCoordinates = new Float32Array([0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
var itemSize = 2;


/**
 * For each shader, attach vertex and texture coordinates
 */
function setupAllShaders(gl, programs)
{        
    return new Promise(function(resolve, reject) {
        Promise.all(programs).then(function(programs) {
            for(var i in programs) {
                var program = programs[i];

                gl.useProgram(program);
                
                // Get vertex and texture coordinate locations
                var positionLocation = gl.getAttribLocation(program, 'a_position');
                var texcoordLocation = gl.getAttribLocation(program, 'a_texcoord');

                // Vertex buffer
                var vbuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, vbuffer);
                gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);
                gl.enableVertexAttribArray(positionLocation);
                gl.vertexAttribPointer(positionLocation, itemSize, gl.FLOAT, false, 0, 0);                    
                        
                // Texture coord buffer
                var tbuffer = gl.createBuffer();
                gl.bindBuffer(gl.ARRAY_BUFFER, tbuffer);
                gl.bufferData(gl.ARRAY_BUFFER, textureCoordinates, gl.STATIC_DRAW);
                gl.enableVertexAttribArray(texcoordLocation);
                gl.vertexAttribPointer(texcoordLocation, itemSize, gl.FLOAT, false, 0, 0);                    
            }
            
            resolve(programs);
        }, function(error) {
            reject(error);
        });
    });
}

/** 
 * Setup texture
 */
export function setupTexture(gl, width, height)
{
    var texture = gl.createTexture();
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
export function setupFramebufferWithTexture(gl, texture)
{
    var fb = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, fb);
    
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture, 0);
    
    return fb;
}


/**
 * Setup program
 */
export function setupProgram(gl, shaders)
{
    return new Promise(function(resolve, reject) {
        Promise.all(shaders).then(function(shaders) {
            var program = gl.createProgram();
            for(var i = 0; i < shaders.length; i++) {
                gl.attachShader(program, shaders[i]);
            }
            gl.linkProgram(program);
            
            if(!gl.getProgramParameter(program, gl.LINK_STATUS))
                reject(gl.getProgramInfoLog(program));
                
            resolve(program);   
        }, function(error) {
            reject(error);
        });
    });
}


/**
 * Sets up a shader from (string) source
 */
function setupShaderFromString(gl, type, source)
{
    // Concatenate source if it's an array
    if(Array.isArray(source)) {        
        source = source.join("\n");
    }
    
    return new Promise(function(resolve, reject) {
        // Convert type-string to integer
        if(type == "vertex")
            type = gl.VERTEX_SHADER;
        else if(type == "fragment")
            type = gl.FRAGMENT_SHADER;
        else
            reject("Invalid shader type, should be 'vertex' or 'fragment'.");        
            
        // Create and compile shader
        var reference = gl.createShader(type);                        
        gl.shaderSource(reference, source);
        gl.compileShader(reference);
        
        // Check status and return on error
        if (!gl.getShaderParameter(reference, gl.COMPILE_STATUS)) {
            var log = gl.getShaderInfoLog(reference);
            console.warn(log);
            reject(log);        
        }
        
        // Return reference
        resolve(reference);
    });
}


/**
 * Load and compile a shader from file
 */
export function setupShaderFromFile(gl, type, source)
{
    if(!Array.isArray(source))
        source = [source];
    
    var promises = [];
    for(let i in source) {
        if(source[i] in storedFiles) {
            let code = storedFiles[source[i]];
            promises.push(new Promise(function(resolve, reject) {
                resolve(code);
            }));
        } else {
            promises.push($.get(source[i]));
        }
    }
    
    return new Promise(function(resolve, reject) {
        Promise.all(promises).then(function(source) {
            setupShaderFromString(gl, type, source).then(function(reference) {
                resolve(reference);
            }, function(error) {
                reject(error);
            });
        }, function(error) {
            reject(error); 
        });
    });
}

