precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;

void main() {
    vec4 color = texture2D(u_texture, v_texcoord);

    float v = max(max(color.r, color.g), color.b);
    float vmin = min(min(color.r, color.g), color.b);
    
    float diff = v - vmin;

    // Compute hue
    float h;
    if(v == color.r) {
        h = color.g - color.b;
    } else if(v == color.g) {
        h = color.b - color.r + 2.0 * diff;
    } else if(v == color.b) {
        h = color.r - color.g + 4.0 * diff;
    }
    
    float hr = 180.0;
    float hdiv = floor((hr * 682.0) / diff);
    h = floor(floor(h * hdiv + 2048.0) / 4096.0);
    if(h < 0.0) h += hr;
    
    // Compute saturation
    float s = floor(floor(diff * floor(1044480.0 / v) + 2048.0) / 4096.0);
    
    // Fill result
    gl_FragColor.a = 1.0;
    gl_FragColor.b = h / 255.0;    
    gl_FragColor.g = s / 255.0;
    gl_FragColor.r = v;
}
