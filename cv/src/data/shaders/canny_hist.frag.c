precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;

void main() {
    vec4 scores[9];

    scores[4] = texture2D(u_texture, v_texcoord);  

    gl_FragColor = scores[4];

    if(scores[4].r >= 0.25 && scores[4].r <= 0.75) {
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

        if(scores[0].r > 0.75 || scores[1].r > 0.75 || scores[2].r > 0.75 ||
           scores[3].r > 0.75 || scores[5].r > 0.75 ||
           scores[6].r > 0.75 || scores[7].r > 0.75 || scores[8].r > 0.75) {
               gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
           } else {
               gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
           }
    }
}
