precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;
uniform bool reportMagOri;

#define PI 3.1415926535897932384626433832795

/**
 * Perform 3x3 sobel
 * If reportMagOri is false:
 *   r -> Horizontal
 *   g -> Vertical
 * If reportMagOri is true:
 *   r -> Magnitude
 *   g -> Orientation
 * 
 */
void main() {
    vec4 scores[9];
    // Top row
    scores[0] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
    scores[1] = texture2D(u_texture, vec2(v_texcoord.x + 0.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
    scores[2] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
       
    // Middle row
    scores[3] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y));
    scores[4] = texture2D(u_texture, v_texcoord);  
    scores[5] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y));
    
    // Bottom row 
    scores[6] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));
    scores[7] = texture2D(u_texture, vec2(v_texcoord.x + 0.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));
    scores[8] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));

    if((v_texcoord.x - 1.0 * pixelSize.x) < 0.0)
    {
        scores[0] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[3] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[6] = vec4(0.0, 0.0, 0.0, 1.0);
    } else if(v_texcoord.x + 1.0 * pixelSize.x > 1.0) {
        scores[2] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[5] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[8] = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    if((v_texcoord.y - 1.0 * pixelSize.y) < 0.0)
    {
        scores[0] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[1] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[2] = vec4(0.0, 0.0, 0.0, 1.0);
    } else if(v_texcoord.y + 1.0 * pixelSize.y > 1.0) {
        scores[6] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[7] = vec4(0.0, 0.0, 0.0, 1.0);
        scores[8] = vec4(0.0, 0.0, 0.0, 1.0);
    }    
    
    float horizontal = -1.0 * scores[0].r + -2.0 * scores[3].r + -1.0 * scores[6].r + 
                       +1.0 * scores[2].r + +2.0 * scores[5].r + +1.0 * scores[8].r;
                     
    float vertical = -1.0 * scores[0].r + -2.0 * scores[1].r + -1.0 * scores[2].r + 
                     +1.0 * scores[6].r + +2.0 * scores[7].r + +1.0 * scores[8].r;

    if(reportMagOri) {
        gl_FragColor.r = sqrt(horizontal * horizontal + vertical * vertical);
        float orientation = atan(vertical, horizontal);
        
        if(orientation < 1.0/8.0 * PI) {
            gl_FragColor.g = 2.0/3.0;
        } else if(orientation < 3.0/8.0 * PI) {
            gl_FragColor.g = 1.0/3.0;
        } else if(orientation < 5.0/8.0 * PI) {
            gl_FragColor.g = 0.0;
        } else if(orientation < 7.0/8.0 * PI) {
            gl_FragColor.g = 3.0/3.0;
        } else if(orientation < 9.0/8.0 * PI) {
            gl_FragColor.g = 2.0/3.0;
        } else if(orientation < 11.0/8.0 * PI) {
            gl_FragColor.g = 1.0/3.0;
        } else if(orientation < 13.0/8.0 * PI) {
            gl_FragColor.g = 0.0/3.0;
        } else if(orientation < 15.0/8.0 * PI) {
            gl_FragColor.g = 3.0/3.0;
        } else {
            gl_FragColor.g = 2.0/3.0;
        }        
    } else {
        gl_FragColor.r = horizontal;
        gl_FragColor.g = vertical;
    }
                     
    gl_FragColor.a = 1.0;
}
