precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;
uniform int channel;

void main() {
    vec4 color = texture2D(u_texture, v_texcoord);
    float value;

    if(channel == 0) {
        value = color.r;
    } else if(channel == 1) {
        value = color.g;
    } else if(channel == 2) {
        value = color.b;
    }

    gl_FragColor = vec4(value, value, value, 1.0);
}
