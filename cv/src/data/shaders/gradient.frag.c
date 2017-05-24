precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;

void main() {
    vec4 scores[9];
    // Top row
    //scores[0] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
    scores[1] = texture2D(u_texture, vec2(v_texcoord.x + 0.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
    //scores[2] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y));
       
    // Middle row
    scores[3] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y));
    //scores[4] = texture2D(u_texture, v_texcoord);  
    scores[5] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y));
    
    // Bottom row 
    //scores[6] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));
    scores[7] = texture2D(u_texture, vec2(v_texcoord.x + 0.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));
    //scores[8] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y));

    float horizontal = (scores[5].x - scores[3].x) / 2.0;
    float vertical = (scores[7].x - scores[1].x) / 2.0;
    float magnitude = sqrt(horizontal * horizontal + vertical * vertical);

    gl_FragColor.r = horizontal + 0.5;
    gl_FragColor.g = vertical + 0.5;
    gl_FragColor.b = magnitude / sqrt(0.5);

    gl_FragColor.a = 1.0;
}
