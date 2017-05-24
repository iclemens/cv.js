precision highp float;

varying vec2 v_texcoord;
uniform sampler2D u_texture;

uniform vec2 pixelSize;
uniform float lowThreshold;
uniform float highThreshold;
uniform bool L2gradient;

#define PI 3.1415926535897932384626433832795

/**
 * Applies Sobel kernel to coordinate
 * returns x and y gradient
 */
vec2 sobel(vec2 coord) 
{
  vec4 scores[9];
  
  // Top row
  scores[0] = texture2D(u_texture, vec2(coord.x - 1.0 * pixelSize.x, coord.y - 1.0 * pixelSize.y));
  scores[1] = texture2D(u_texture, vec2(coord.x + 0.0 * pixelSize.x, coord.y - 1.0 * pixelSize.y));
  scores[2] = texture2D(u_texture, vec2(coord.x + 1.0 * pixelSize.x, coord.y - 1.0 * pixelSize.y));
    
  // Middle row
  scores[3] = texture2D(u_texture, vec2(coord.x - 1.0 * pixelSize.x, coord.y)); 
  scores[5] = texture2D(u_texture, vec2(coord.x + 1.0 * pixelSize.x, coord.y));
  
  // Bottom row 
  scores[6] = texture2D(u_texture, vec2(coord.x - 1.0 * pixelSize.x, coord.y + 1.0 * pixelSize.y));
  scores[7] = texture2D(u_texture, vec2(coord.x + 0.0 * pixelSize.x, coord.y + 1.0 * pixelSize.y));
  scores[8] = texture2D(u_texture, vec2(coord.x + 1.0 * pixelSize.x, coord.y + 1.0 * pixelSize.y));
  
  if((coord.x - 1.0 * pixelSize.x) < 0.0)
  {
      scores[0] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[3] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[6] = vec4(0.0, 0.0, 0.0, 1.0);
  } else if(coord.x + 1.0 * pixelSize.x > 1.0) {
      scores[2] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[5] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[8] = vec4(0.0, 0.0, 0.0, 1.0);
  }
  
  if((coord.y - 1.0 * pixelSize.y) < 0.0)
  {
      scores[0] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[1] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[2] = vec4(0.0, 0.0, 0.0, 1.0);
  } else if(coord.y + 1.0 * pixelSize.y > 1.0) {
      scores[6] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[7] = vec4(0.0, 0.0, 0.0, 1.0);
      scores[8] = vec4(0.0, 0.0, 0.0, 1.0);
  }    

  /**
   * Horizontal gradient
   * [-1 0 +1]
   * [-2 0 +2]
   * [-1 0 +1]
   */  
  float Gx =
     -1.0 * scores[0].r + -2.0 * scores[3].r + -1.0 * scores[6].r + 
     +1.0 * scores[2].r + +2.0 * scores[5].r + +1.0 * scores[8].r;
     
  /**
   * Vertical gradient
   * [-1 -2 -1]
   * [ 0  0  0]
   * [+1 +2 +1]
   */
  float Gy = 
     -1.0 * scores[0].r + -2.0 * scores[1].r + -1.0 * scores[2].r + 
     +1.0 * scores[6].r + +2.0 * scores[7].r + +1.0 * scores[8].r;
     
  return vec2(Gx, Gy);
}


/**
 * Convert Sobel gradient into angle / quadrant
 * 3 2 1
 * 0   0
 * 1 2 3
 */
int sobel2orientation(vec2 s)
{
  // Returns value [-pi, pi] with 0 begin positive x (quadrant 0)
  float orientation = atan(-s.y, s.x) / PI;
  
  if(orientation < -7.0/8.0) {
      return 0;
  } else if(orientation < -5.0/8.0) {
      return 1;
  } else if(orientation < -3.0/8.0) {
      return 2;
  } else if(orientation < -1.0/8.0) {
      return 3;
  } else if(orientation < 1.0/8.0) {
      return 0;
  } else if(orientation < 3.0/8.0) {
      return 1;
  } else if(orientation < 5.0/8.0) {
      return 2;
  } else if(orientation < 7.0/8.0) {
      return 3;
  } else {
      return 0;
  }    
}


float sobel2magnitude(vec2 s) 
{
    if(L2gradient)
        return sqrt(s.x * s.x + s.y * s.y);
    else
        return abs(s.x) + abs(s.y);
}

void main() {
    vec2 centre = sobel(v_texcoord);
    float magnitude = sobel2magnitude(centre);    
    int orientation = sobel2orientation(centre);
    
    float result = 0.0;
    
    if(magnitude > lowThreshold) {
      result = 0.5;
      
      float prev = 0.0;
      float next = 0.0;
      
      // Based on the direction of the sobel gradient, check if we're the maximum
      if(orientation == 0) {
        // Left/right
        prev = sobel2magnitude(sobel( vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y) )); 
        next = sobel2magnitude(sobel( vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y) ));
      } else if(orientation == 3) {
        // Top-left to bottom-right
        prev = sobel2magnitude(sobel( vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y) )); 
        next = sobel2magnitude(sobel( vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y) ));
      } else if(orientation == 2) {
        // Top to bottom
        prev = sobel2magnitude(sobel( vec2(v_texcoord.x, v_texcoord.y - 1.0 * pixelSize.y) )); 
        next = sobel2magnitude(sobel( vec2(v_texcoord.x, v_texcoord.y + 1.0 * pixelSize.y) ));
      } else if(orientation == 1) {
        // Top-right to bottom-left
        prev = sobel2magnitude(sobel( vec2(v_texcoord.x + 1.0 * pixelSize.x, v_texcoord.y - 1.0 * pixelSize.y) )); 
        next = sobel2magnitude(sobel( vec2(v_texcoord.x - 1.0 * pixelSize.x, v_texcoord.y + 1.0 * pixelSize.y) ));
      }
      
      if(magnitude > prev && magnitude >= next) {
        if(magnitude > highThreshold)
          result = 1.0;
        else
          result = 0.0;
      }
    }

    gl_FragColor.r = result;
    gl_FragColor.g = result;
    gl_FragColor.b = result;

    gl_FragColor.a = 1.0;
}
