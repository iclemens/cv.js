precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;
uniform int S;
uniform int mask;
uniform float T;


/**
 * Output:
 *  x -> Score of the feature
 *  y/z/w -> Same as x
 */
void main() {    
    float score = 0.0;
    if(mask == 16)
        score = fast_16_S_score(v_texcoord, u_texture, pixelSize, S) - 1.0 / 256.0;
    else
        score = fast_8_S_score(v_texcoord, u_texture, pixelSize, S) - 1.0 / 256.0;

    if(score < T) {
        gl_FragColor = vec4(score, 0.0, 0.0, 1.0);
    } else {
        gl_FragColor = vec4(score, score, score, 1.0);
    }
}
