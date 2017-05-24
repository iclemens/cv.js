precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;

void main() {
    vec4 color = texture2D(u_texture, v_texcoord);

    //float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    float gray = dot(color.rgb, vec3(4899.0, 9617.0, 1868.0)) / 16384.0;

    color = vec4(gray, gray, gray, 1.0);
    gl_FragColor = floor(255.0 * color + 0.5) / 255.0;
}
