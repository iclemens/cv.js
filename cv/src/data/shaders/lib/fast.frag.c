/**
 * Shader implementation of the FAST [1] algorithm.
 *
 * Copyright (C) 2015-2016 Ivar Clemens
 *
 * [1] Fusing points and lines for high performance tracking, Rosten and Drummond
 *
 * Usage:
 *  fast_8_S_score(vec2 coordinate, sampler2D texture, vec2 pixelSize, int S)
 *  fast_16_S_score(vec2 coordinate, sampler2D texture, vec2 pixelSize, int S)
 */
precision highp float;

bool is_a_corner_16(float pixel, float mask[16], int S, float t)
{
    // Lower and higher thresholds
    float t_low = pixel - t;
    float t_high = pixel + t;
    
    bool result = false;
    
    int low_run = 0;
    int high_run = 0;
    int first_low_run = -1;
    int first_high_run = -1;
    
    for(int i = 0; i < 16; i++) {
        // Check for low-run
        if(mask[i] < t_low) {
            low_run++;
        } else {
            if(first_low_run == -1)
                first_low_run = low_run;
            if(low_run >= S)
                result = true;
            low_run = 0;
        }
        
        // Check for high-run
        if(mask[i] > t_high) {
            high_run++;
        } else {
            if(first_high_run == -1)
                first_high_run = high_run;
            if(high_run >= S)
                result = true;
            high_run = 0;
        }
    }
    
    // Make sure segment does not loop around
    if((low_run + first_low_run) >= S || low_run >= S ||
       (high_run + first_high_run) >= S || high_run >= S) {
        result = true;
    }
    
    return result;
} 


bool is_a_corner_8(float pixel, float mask[8], int S, float t)
{
    // Lower and higher thresholds
    float t_low = pixel - t;
    float t_high = pixel + t;
    
    bool result = false;
    
    int low_run = 0;
    int high_run = 0;
    int first_low_run = -1;
    int first_high_run = -1;
    
    for(int i = 0; i < 8; i++) {
        // Check for low-run
        if(mask[i] < t_low) {
            low_run++;
        } else {
            if(first_low_run == -1)
                first_low_run = low_run;
            if(low_run >= S)
                result = true;
            low_run = 0;
        }
        
        // Check for high-run
        if(mask[i] > t_high) {
            high_run++;
        } else {
            if(first_high_run == -1)
                first_high_run = high_run;
            if(high_run >= S)
                result = true;
            high_run = 0;
        }
    }
    
    // Make sure segment does not loop around
    if((low_run + first_low_run) >= S || low_run >= S ||
       (high_run + first_high_run) >= S || high_run >= S) {
        result = true;
    }
    
    return result;
} 


float fast_8_S_score(vec2 coordinate, sampler2D texture, vec2 pixelSize, int S)
{
    float mask[8];
    mask[0] = texture2D(texture, vec2(coordinate.x - 1.0 * pixelSize.x, coordinate.y - 1.0 * pixelSize.y)).x;
    mask[1] = texture2D(texture, vec2(coordinate.x + 0.0 * pixelSize.x, coordinate.y - 1.0 * pixelSize.y)).x;
    mask[2] = texture2D(texture, vec2(coordinate.x + 1.0 * pixelSize.x, coordinate.y - 1.0 * pixelSize.y)).x;
    mask[3] = texture2D(texture, vec2(coordinate.x + 1.0 * pixelSize.x, coordinate.y + 0.0 * pixelSize.y)).x;  
    mask[4] = texture2D(texture, vec2(coordinate.x + 1.0 * pixelSize.x, coordinate.y + 1.0 * pixelSize.y)).x; 
    mask[5] = texture2D(texture, vec2(coordinate.x + 0.0 * pixelSize.x, coordinate.y + 1.0 * pixelSize.y)).x;
    mask[6] = texture2D(texture, vec2(coordinate.x - 1.0 * pixelSize.x, coordinate.y + 1.0 * pixelSize.y)).x;
    mask[7] = texture2D(texture, vec2(coordinate.x - 1.0 * pixelSize.x, coordinate.y + 0.0 * pixelSize.y)).x;
    
    /*
    for(int i = 8; i < 13; i++)
        mask[i] = mask[i - 8];
    
    float pixel = texture2D(texture, coordinate).x;
    
    for(int i = 0; i < 13; i++)
        mask[i] = pixel - mask[i];
       
    float threshold = 10.0/255.0;
        
    float a0 = threshold;
    for(int k = 0; k < 8; k += 2 )
    {
        float a = min(mask[k+1], mask[k+2]);
        if( a <= a0 )
            continue;
        a = min(a, mask[k+3]);
        a = min(a, mask[k+4]);
        a0 = max(a0, min(a, mask[k]));
        a0 = max(a0, min(a, mask[k+5]));
    }

    float b0 = -a0;
    for(int k = 0; k < 8; k += 2 )
    {
        float b = max(mask[k+1], mask[k+2]);
        b = max(b, mask[k+3]);
        if( b >= b0 )
            continue;
        b = max(b, mask[k+4]);

        b0 = min(b0, max(b, mask[k]));
        b0 = min(b0, max(b, mask[k+5]));
    }    

    threshold = -b0;
    
    return threshold;    */
    
   
    // Reject if we're processing an edge pixel
    if(coordinate.x < 1.0 * pixelSize.x || 
       coordinate.y < 1.0 * pixelSize.y ||
       coordinate.x > 1.0 - 1.0 * pixelSize.x ||
       coordinate.y > 1.0 - 1.0 * pixelSize.y)
        return 0.0;
    
    // Central pixel value
    float pixel = texture2D(texture, coordinate).x;
    
    float t_min = 0.0;
    float t_max = 1.0;    
    
    // Binary search for threshold
    for(int q = 0; q < 8; q++) {
        float t = (t_max + t_min) / 2.0;
        
        if(is_a_corner_8(pixel, mask, S, t))
            t_min = t;
        else
            t_max = t;
    }
    
    return (t_max + t_min) / 2.0;
}


float fast_16_S_score(vec2 coordinate, sampler2D texture, vec2 pixelSize, int S)
{
    // Get values for surrounding pixels
    float mask[16];
    mask[0] = texture2D(texture, vec2(coordinate.x - 3.0 * pixelSize.x, coordinate.y + 0.0 * pixelSize.y)).x;          
    mask[1] = texture2D(texture, vec2(coordinate.x - 3.0 * pixelSize.x, coordinate.y - 1.0 * pixelSize.y)).x;
    mask[2] = texture2D(texture, vec2(coordinate.x - 2.0 * pixelSize.x, coordinate.y - 2.0 * pixelSize.y)).x;
    mask[3] = texture2D(texture, vec2(coordinate.x - 1.0 * pixelSize.x, coordinate.y - 3.0 * pixelSize.y)).x;
    mask[4] = texture2D(texture, vec2(coordinate.x + 0.0 * pixelSize.x, coordinate.y - 3.0 * pixelSize.y)).x;
    mask[5] = texture2D(texture, vec2(coordinate.x + 1.0 * pixelSize.x, coordinate.y - 3.0 * pixelSize.y)).x;
    mask[6] = texture2D(texture, vec2(coordinate.x + 2.0 * pixelSize.x, coordinate.y - 2.0 * pixelSize.y)).x;
    mask[7] = texture2D(texture, vec2(coordinate.x + 3.0 * pixelSize.x, coordinate.y - 1.0 * pixelSize.y)).x;
    mask[8] = texture2D(texture, vec2(coordinate.x + 3.0 * pixelSize.x, coordinate.y + 0.0 * pixelSize.y)).x;
    mask[9] = texture2D(texture, vec2(coordinate.x + 3.0 * pixelSize.x, coordinate.y + 1.0 * pixelSize.y)).x;
    mask[10] = texture2D(texture, vec2(coordinate.x + 2.0 * pixelSize.x, coordinate.y + 2.0 * pixelSize.y)).x;
    mask[11] = texture2D(texture, vec2(coordinate.x + 1.0 * pixelSize.x, coordinate.y + 3.0 * pixelSize.y)).x;
    mask[12] = texture2D(texture, vec2(coordinate.x + 0.0 * pixelSize.x, coordinate.y + 3.0 * pixelSize.y)).x;
    mask[13] = texture2D(texture, vec2(coordinate.x - 1.0 * pixelSize.x, coordinate.y + 3.0 * pixelSize.y)).x;
    mask[14] = texture2D(texture, vec2(coordinate.x - 2.0 * pixelSize.x, coordinate.y + 2.0 * pixelSize.y)).x;
    mask[15] = texture2D(texture, vec2(coordinate.x - 3.0 * pixelSize.x, coordinate.y + 1.0 * pixelSize.y)).x;    
    
    // Reject if we're processing an edge pixel
    if(coordinate.x < 3.0 * pixelSize.x || 
       coordinate.y < 3.0 * pixelSize.y ||
       coordinate.x > 1.0 - 3.0 * pixelSize.x ||
       coordinate.y > 1.0 - 3.0 * pixelSize.y)
        return 0.0;
    
    // Central pixel value
    float pixel = texture2D(texture, coordinate).x;
    
    float t_min = 0.0;
    float t_max = 1.0;
    
    // Binary search for threshold
    for(int q = 0; q < 8; q++) {
        float t = (t_max + t_min) / 2.0;
        
        if(is_a_corner_16(pixel, mask, S, t))
            t_min = t;
        else
            t_max = t;
    }
    
    return (t_max + t_min) / 2.0;    
}
