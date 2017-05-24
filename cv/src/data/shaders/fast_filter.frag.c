precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;
uniform float T;
uniform int subPixel;

#define sc(r,c) scores[r * 3 + c] 

vec3 subpixel2D(float scores[9])
{
    // the coefficients of the 2d quadratic function least-squares fit:
    float tmp1 = sc(0,0) + sc(0,2) - 2.0 * sc(1,1) + sc(2,0) + sc(2,2);
    float coeff1 = 3.0 * (tmp1 + sc(0,1) - ((sc(1,0) + sc(1,2)) * 2.0) + sc(2,1));
    float coeff2 = 3.0 * (tmp1 - ((sc(0,1) + sc(2,1)) * 2.0) + sc(1,0) + sc(1,2));
    float tmp2 = sc(0,2) - sc(2,0);
    float tmp3 = (sc(0,0) + tmp2 - sc(2,2));
    float tmp4 = tmp3 - 2.0 * tmp2;
    float coeff3 = -3.0 * (tmp3 + sc(0,1) - sc(2,1));
    float coeff4 = -3.0 * (tmp4 + sc(1,0) - sc(1,2));
    float coeff5 = (sc(0,0) - sc(0,2) - sc(2,0) + sc(2,2)) * 2.0;
    float coeff6 = -(sc(0,0) + sc(0,2) - ((sc(1,0) + sc(0,1) + sc(1,2) + sc(2,1)) * 2.0) - 5.0 * sc(1,1) + sc(2,0) + sc(2,2)) * 2.0;

    // 2nd derivative test:
    float H_det = 4.0 * coeff1 * coeff2 - coeff5 * coeff5;
    
    if(H_det == 0.0) {
        return vec3(coeff6 / 18.0, 0.0, 0.0);
    }
    
    // The maximum must be at one of the 4 patch corners
    if(!(H_det > 0.0 && coeff1 < 0.0)) {
        float tmp_max = coeff3 + coeff4 + coeff5;
        float delta_x = 1.0;
        float delta_y = 1.0;
        
        float tmp = -coeff3 + coeff4 - coeff5;
        if(tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = -1.0;
            delta_y = 1.0;
        }
        
        tmp = coeff3 - coeff4 - coeff5;
        if(tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = 1.0;
            delta_y = -1.0;
        }
        
        tmp = -coeff3 - coeff4 + coeff5;
        if(tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = -1.0;
            delta_y = -1.0;
        }
        
        return vec3((tmp_max + coeff1 + coeff2 + coeff6) / 18.0, delta_x, delta_y);
    }
    
    // Location of maximum
    float delta_x = (2.0 * coeff2 * coeff3 - coeff4 * coeff5) / -H_det;
    float delta_y = (2.0 * coeff1 * coeff4 - coeff3 * coeff5) / -H_det;
    
    // Mmaximum is outside of boundaries
    bool tx = false;
    bool tx_ = false;
    bool ty = false;
    bool ty_ = false;
    
    if(delta_x > 1.0)
        tx = true;
    else if(delta_x < -1.0)
        tx_ = true;
    if(delta_y > 1.0)
        ty = true;
    if(delta_y < -1.0)
        ty = true;
        
    if(tx || tx_ || ty || ty_) {
        float delta_x1 = 0.0, delta_x2 = 0.0, delta_y1 = 0.0, delta_y2 = 0.0;
        if(tx) {
            delta_x1 = 1.0;
            delta_y1 = (coeff4 + coeff5) / (2.0 * coeff2);
            if(delta_y1 > 1.0)
                delta_y1 = 1.0;
            else if(delta_y1 < -1.0)
                delta_y1 = -1.0;
        } else if(tx_) {
            delta_x1 = -1.0;
            delta_y1 = -(coeff4 - coeff5) / (2.0 * coeff2);
            if(delta_y1 > 1.0)
                delta_y1 = 1.0;
            else if(delta_y1 < -1.0)
                delta_y1 = -1.0;
        }
        
        if (ty) {
            delta_y2 = 1.0;
            delta_x2 = -(coeff3 + coeff5) / (2.0 * coeff1);
            if (delta_x2 > 1.0)
                delta_x2 = 1.0;
            else if (delta_x2 < -1.0)
                delta_x2 = -1.0;
        } else if (ty_) {
            delta_y2 = -1.0;
            delta_x2 = -(coeff3 - coeff5) / (2.0 * coeff1);
            if (delta_x2 > 1.0)
                delta_x2 = 1.0;
            else if (delta_x2 < -1.0)
                delta_x2 = -1.0;
        }
        
        float max1 = (coeff1 * delta_x1 * delta_x1 + coeff2 * delta_y1 * delta_y1 + coeff3 * delta_x1 + coeff4 * delta_y1 + coeff5 * delta_x1 * delta_y1 + coeff6) / 18.0;
        float max2 = (coeff1 * delta_x2 * delta_x2 + coeff2 * delta_y2 * delta_y2 + coeff3 * delta_x2 + coeff4 * delta_y2 + coeff5 * delta_x2 * delta_y2 + coeff6) / 18.0;
        
        if (max1 > max2) {
            return vec3(max1, delta_x1, delta_y1);
        } else {
            return vec3(max2, delta_x2, delta_y2);
        }        
    }
    
    float score = (coeff1 * delta_x * delta_x + coeff2 * delta_y * delta_y + coeff3 * delta_x + coeff4 * delta_y + coeff5 * delta_x * delta_y + coeff6) / 18.0;    
    return vec3(score, delta_x, delta_y);
}

void main() {   
    float scores[9];
    // Top row
    scores[0] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y)).x;
    scores[1] = texture2D(u_texture, vec2(v_texcoord.x, v_texcoord.y - 1.0 * pixelSize.y)).x;
    scores[2] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y)).x;
       
    // Middle row
    scores[3] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y)).x;
    scores[4] = texture2D(u_texture, v_texcoord).x;  
    scores[5] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y)).x;
    
    // Bottom row 
    scores[6] = texture2D(u_texture, vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y)).x;
    scores[7] = texture2D(u_texture, vec2(v_texcoord.x, v_texcoord.y + 1.0 * pixelSize.y)).x;
    scores[8] = texture2D(u_texture, vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y)).x;

    // Only use scores[4] if it is the largest in the region
    if(scores[4] > scores[0] && scores[4] > scores[1] && scores[4] > scores[2] && scores[4] > scores[3] &&
       scores[4] > scores[5] && scores[4] > scores[6] && scores[4] > scores[7] && scores[4] > scores[8] && 
       texture2D(u_texture, v_texcoord).w > 0.0) {
           if(subPixel == 1) {
               gl_FragColor.xyw = subpixel2D(scores);
           } else {
                gl_FragColor.x = scores[4];           
                gl_FragColor.w = scores[4];
           }
    } else {
        gl_FragColor.x = 0.0;
        gl_FragColor.w = 0.0;
    }
}
