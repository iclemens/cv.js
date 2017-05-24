precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;

void main() {        
    vec4 color = texture2D(u_texture, v_texcoord);
    gl_FragColor = color;
}
