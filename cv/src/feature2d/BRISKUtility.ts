
import {Keypoint} from '../core/Keypoint'

/**
 * SubPixel interpolation based on a 3x3 window
 */
export function subPixel2D(s_0_0: number, s_0_1: number, s_0_2: number, 
                    s_1_0: number, s_1_1: number, s_1_2: number, 
                    s_2_0: number, s_2_1: number, s_2_2: number): Keypoint
{
    // the coefficients of the 2d quadratic function least-squares fit:
    var tmp1 = s_0_0 + s_0_2 - 2 * s_1_1 + s_2_0 + s_2_2;
    var coeff1 = 3 * (tmp1 + s_0_1 - ((s_1_0 + s_1_2) * 2) + s_2_1);
    var coeff2 = 3 * (tmp1 - ((s_0_1 + s_2_1) * 2) + s_1_0 + s_1_2);
    var tmp2 = s_0_2 - s_2_0;
    var tmp3 = (s_0_0 + tmp2 - s_2_2);
    var tmp4 = tmp3 - 2 * tmp2;
    var coeff3 = -3 * (tmp3 + s_0_1 - s_2_1);
    var coeff4 = -3 * (tmp4 + s_1_0 - s_1_2);
    var coeff5 = (s_0_0 - s_0_2 - s_2_0 + s_2_2) << 2;
    var coeff6 = -(s_0_0 + s_0_2 - ((s_1_0 + s_0_1 + s_1_2 + s_2_1) * 2) - 5 * s_1_1 + s_2_0 + s_2_2) * 2;

    // 2nd derivative test:
    var H_det = 4 * coeff1 * coeff2 - coeff5 * coeff5;
    
    if(H_det == 0) {
        return {'x': 0.0, 'y': 0.0, 'score': coeff6 / 18.0};
    }
                
    if(!(H_det > 0 && coeff1 < 0)) {
        // The maximum must be at the one of the 4 patch corners.
        var c_scores = [
            coeff3 + coeff4 + coeff5,
            -coeff3 + coeff4 - coeff5,
            coeff3 - coeff4 - coeff5,
            -coeff3 - coeff4 + coeff5                    
        ];
        
        var tmp_max = coeff3 + coeff4 + coeff5;
        delta_x = 1.0;
        delta_y = 1.0;

        var tmp = -coeff3 + coeff4 - coeff5;
        if (tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = -1.0;
            delta_y = 1.0;
        }
        
        tmp = coeff3 - coeff4 - coeff5;
        if (tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = 1.0;
            delta_y = -1.0;
        }
        
        tmp = -coeff3 - coeff4 + coeff5;
        if (tmp > tmp_max) {
            tmp_max = tmp;
            delta_x = -1.0;
            delta_y = -1.0;
        }
                        
        return {'x': delta_x, 'y': delta_y, 'score': (tmp_max + coeff1 + coeff2 + coeff6) / 18.0};
    }
    
    // this is hopefully the normal outcome of the Hessian test
    var delta_x = (2 * coeff2 * coeff3 - coeff4 * coeff5) / (-H_det);
    var delta_y = (2 * coeff1 * coeff4 - coeff3 * coeff5) / (-H_det);
    
    // TODO: this is not correct, but easy, so perform a real boundary maximum search:
    var tx = false;
    var tx_ = false;
    var ty = false;
    var ty_ = false;
    
    if (delta_x > 1.0)
        tx = true;
    else if (delta_x < -1.0)
        tx_ = true;
    if (delta_y > 1.0)
        ty = true;
    if (delta_y < -1.0)
        ty_ = true;
        
    if (tx || tx_ || ty || ty_) {
        // get two candidates:
        var delta_x1 = 0.0;
        var delta_x2 = 0.0;
        var delta_y1 = 0.0;
        var delta_y2 = 0.0;
        
        if (tx) {
            delta_x1 = 1.0;
            delta_y1 = -(coeff4 + coeff5) / (2 * coeff2);
            if (delta_y1 > 1.0)
                delta_y1 = 1.0;
            else if (delta_y1 < -1.0)
                delta_y1 = -1.0;
        } else if (tx_) {
            delta_x1 = -1.0;
            delta_y1 = -(coeff4 - coeff5) / (2 * coeff2);
            if (delta_y1 > 1.0)
                delta_y1 = 1.0;
            else if (delta_y1 < -1.0)
                delta_y1 = -1.0;
        }

        if (ty)
        {
            delta_y2 = 1.0;
            delta_x2 = -(coeff3 + coeff5) / (2 * coeff1);
            if (delta_x2 > 1.0)
                delta_x2 = 1.0;
            else if (delta_x2 < -1.0)
                delta_x2 = -1.0;
        } else if (ty_) {
            delta_y2 = -1.0;
            delta_x2 = -(coeff3 - coeff5) / (2 * coeff1);
            if (delta_x2 > 1.0)
                delta_x2 = 1.0;
            else if (delta_x2 < -1.0)
                delta_x2 = -1.0;
        }
        
        // insert both options for evaluation which to pick
        var max1 = (coeff1 * delta_x1 * delta_x1 + coeff2 * delta_y1 * delta_y1 + coeff3 * delta_x1 + coeff4 * delta_y1
            + coeff5 * delta_x1 * delta_y1 + coeff6) / 18.0;
        var max2 = (coeff1 * delta_x2 * delta_x2 + coeff2 * delta_y2 * delta_y2 + coeff3 * delta_x2 + coeff4 * delta_y2
            + coeff5 * delta_x2 * delta_y2 + coeff6) / 18.0;

        if (max1 > max2)
            return {'x': delta_x1, 'y': delta_y1, 'score': max1};
        else
            return {'x': delta_x2, 'y': delta_y2, 'score': max2};
    }
    
    // this is the case of the maximum inside the boundaries:
    var score = (coeff1 * delta_x * delta_x + coeff2 * delta_y * delta_y + coeff3 * delta_x + coeff4 * delta_y
                    + coeff5 * delta_x * delta_y + coeff6) / 18.0;

    return {'x': delta_x, 'y': delta_y, 'score': score};
}
