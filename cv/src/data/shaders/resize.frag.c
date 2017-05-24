precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSizeIn;
uniform vec2 pixelSizeOut;

uniform float xIn;
uniform float yIn;

uniform float wIn;
uniform float hIn;

void main() {
    // This performs cropping and resizing
    vec2 Tcoord = (vec2(xIn, yIn) + v_texcoord * vec2(wIn, hIn)) * pixelSizeIn;
    gl_FragColor = texture2D(u_texture, Tcoord);
}
