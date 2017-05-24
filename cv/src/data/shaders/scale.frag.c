precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSizeIn;
uniform vec2 pixelSizeOut;

vec4 scaleHalf()
{
    vec2 top_left = v_texcoord;
    vec2 top_right = v_texcoord;
    vec2 bottom_left = v_texcoord;
    vec2 bottom_right = v_texcoord;
    
    top_left.y -= 0.5 * pixelSizeIn.y;
    top_right.y -= 0.5 *pixelSizeIn.y;
    
    bottom_left.y += 0.5 * pixelSizeIn.y;
    bottom_right.y += 0.5 * pixelSizeIn.y;
    
    top_left.x -= 0.5 * pixelSizeIn.x;
    bottom_left.x -= 0.5 * pixelSizeIn.x;
    
    top_right.x += 0.5 * pixelSizeIn.x;
    bottom_right.x += 0.5 * pixelSizeIn.x;
    
    vec4 color;
    
    color += texture2D(u_texture, bottom_left) * 255.0;
    color += texture2D(u_texture, bottom_right) * 255.0;

    color +=texture2D(u_texture, top_left) * 255.0;
    color += texture2D(u_texture, top_right) * 255.0;
   
    return floor(color / 4.0 + 0.5) / 255.0;        
}


vec4 scaleTwoThird()
{
    // First determine which quadrant of the 2x2 field we are in    
    float xeven = mod(floor(v_texcoord.x / pixelSizeOut.x), 2.0);
    float yeven = mod(floor(v_texcoord.y / pixelSizeOut.y), 2.0);
    
    // Then compute the coordinates of the four pixels
    vec2 A = v_texcoord;
    vec2 B = v_texcoord;
    vec2 C = v_texcoord;
    vec2 D = v_texcoord;
    
    // A B  B A  
    // C D  D C
    //
    // C D  D C
    // A B  B A

    if(xeven < 0.5) {
        A.x = A.x - 0.5 * pixelSizeOut.x + 0.5 * pixelSizeIn.x;        
        B.x = A.x + pixelSizeIn.x;
    } else {
        A.x = A.x - 0.5 * pixelSizeOut.x + 1.0 * pixelSizeIn.x;
        B.x = A.x - pixelSizeIn.x;
    }

    C.x = A.x;   
    D.x = B.x;

    if(yeven < 0.5) {
        A.y = A.y - 0.5 * pixelSizeOut.y + 0.5 * pixelSizeIn.y;
        C.y = A.y + pixelSizeIn.y;
    } else {
        A.y = A.y - 0.5 * pixelSizeOut.y + 1.0 * pixelSizeIn.y;
        C.y = A.y - pixelSizeIn.y;
    }

    B.y = A.y;
    D.y = C.y;

    vec4 color;
    color += texture2D(u_texture, A) * 255.0 * (2.0 / 3.0) * (2.0 / 3.0);
    color += texture2D(u_texture, B) * 255.0 * (2.0 / 3.0) * (1.0 / 3.0);
    color += texture2D(u_texture, C) * 255.0 * (2.0 / 3.0) * (1.0 / 3.0);
    color += texture2D(u_texture, D) * 255.0 * (1.0 / 3.0) * (1.0 / 3.0);

    return floor(color + 0.5) / 255.0;
}


/**
 * This shader only supports 2/3 and 1/2 scaling
 * therefore we check to which one the ratio of pixel sizes
 * is closest in order to determine which scaler to use.
 */
void main() 
{
    vec4 color;

    vec2 ratio = pixelSizeIn / pixelSizeOut;    
    float bound = (0.5 + 2.0/3.0) / 2.0;
    
    if(ratio.x >= bound)
        color = scaleTwoThird();
    else
        color = scaleHalf();
    
    gl_FragColor = color;
}
