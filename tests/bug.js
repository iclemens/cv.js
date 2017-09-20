
// Coordinates
var vertices = new Float32Array([-1, 1, 1, 1, 1, -1, -1, 1, 1, -1, -1, -1]);
var textureCoordinates = new Float32Array([0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
var itemSize = 2;

var fragSource = "precision highp float;\nvarying vec2 v_texcoord;\nuniform sampler2D u_texture;\n" +
    "uniform vec2 pixelSize;\nvoid main() {\nvec4 color = texture2D(u_texture, v_texcoord);\ngl_FragColor = color;\n}";

var vertSource = "attribute vec2 a_position;\nattribute vec2 a_texcoord;\nvarying vec2 v_texcoord;\nvoid main() {\ngl_Position = vec4(a_position, 0.0, 1.0);\nv_texcoord = a_texcoord;\n}";


function setupTexture(gl, image)
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
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
    
    return texture;
}

function setupProgram(gl)
{
    var shaders = [];
    
    shaders[0] = gl.createShader(gl.VERTEX_SHADER);
    shaders[1] = gl.createShader(gl.FRAGMENT_SHADER);
                          
    gl.shaderSource(shaders[0], vertSource);
    gl.shaderSource(shaders[1], fragSource);
    
    var program = gl.createProgram();
    for(var i = 0; i < shaders.length; i++) {
        gl.compileShader(shaders[i]);
        gl.attachShader(program, shaders[i]);
    }
    gl.linkProgram(program);

    
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
    
    return program;
}

function drawTexture(gl, width, height, texture)
{
    gl.viewport(0, 0, width, height);
        
    // Render texture to canvas
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    //gl.useProgram(this.defaultProgram);
    gl.drawArrays(gl.TRIANGLES, 0, 6);
}