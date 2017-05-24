precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSizeIn;
uniform vec2 pixelSizeOut;

// 1  4  6  4 1
// 4 16 24 16 4
// etc..

// Border type is: reflex
// gfedcb|abcdefgh|hgedcb
// if x < 0 => -x
// if x > 1 => 1 - x

vec4 gaussianKernel(sampler2D T, vec2 coord, vec2 size)
{
    vec4 result = vec4(0, 0, 0, 1.0);

    for(int i = -2; i <= 2; i++) {
        for(int j = -2; j <= 2; j++) {
            float x = coord.x + float(i) * size.x;
            float y = coord.y + float(j) * size.y;
            
            // Reflect
            if(x < 0.0) x = 0.0 - x + size.x;
            if(y < 0.0) y = 0.0 - y + size.y;
            if(x > 1.0) x = 2.0 - x - size.x;
            if(y > 1.0) y = 2.0 - y - size.y;
            
            float weight = 1.0;
            
            if(i == -1 || i == 1) weight *= 4.0;
            if(i == 0) weight *= 6.0;
            
            if(j == -1 || j == 1) weight *= 4.0;
            if(j == 0) weight *= 6.0;
            
            result += weight/256.0 * texture2D(T, vec2(x, y));
        }
    }
    
    return result;
}

void main()
{
    vec4 value = gaussianKernel(u_texture, 
        v_texcoord - 0.5 * pixelSizeOut + 0.5 * pixelSizeIn, 
        pixelSizeIn);

    // With 256 => 377126 errors

    gl_FragColor = floor(255.0 * value + 0.501) / 255.0;
    //gl_FragColor = value;
}
