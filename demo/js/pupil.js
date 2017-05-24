
function PupilDetector(CV, context)
{
    this._CV = CV;
    
    this.resize = new CV.Resize();
    this.matGradient = new CV.MatGradient();
    this.pyrDown = new CV.PyrDown();
    
    this.pPupil = new Float64Array(50 * 43);
    this.pupil = [undefined, undefined];
    
    this.kGradientThreshold = 50.0;
    this.kWeightDivisor = 1.0;
    
    this._context = context;
}


PupilDetector.prototype.findPupil = function(image, ROI)
{
    // Extract pixels in ROI
    var cropped = this.resize.cropAndResize(image, ROI[0], ROI[1], ROI[2], ROI[3], 50, 43);
    var croppedI = cropped.asImageData();
    var croppedID = croppedI.getImageData();
    
    // Create blurred copy to use as weight
    var blurred = this.pyrDown.pyrDown(cropped, 50, 43);
    var blurredI = blurred.asImageData();
    var blurredID = blurredI.getImageData();
        
    // Compute gradients
    var gradients = this.matGradient.matGradient(blurred);
    var gradientsI = gradients.asImageData();
    var gradientsID = gradientsI.getImageData();

    var width = cropped.width;
    var height = cropped.height;
    var area = cropped.width * cropped.height
        
    // Reset output
    for(let y = 0; y < height; y++) {
        for(let x = 0; x < width; x++) {
            let offset = (y * width) + x;
            this.pPupil[offset] = 0;
        }
    }        
        
    // Compute mean and std of magnitude
    var mean = 0;
    for(let y = 0; y < height; y++) {
        for(let x = 0; x < width; x++) {
            let offset = ((y * width) + x) * 4;
            mean += gradientsID.data[offset + 2];
        }
    }
    mean /= area;
        
    var std = 0;
    for(let y = 0; y < height; y++) {
        for(let x = 0; x < width; x++) {
            let offset = ((y * width) + x) * 4;
            std += ((gradientsID.data[offset + 2] - mean) * (gradientsID.data[offset + 2] - mean));
        }
    }        
    std = Math.sqrt(std / area);
    
    var stdDev = std / Math.sqrt(area);
    
    // Compute dynamic threshold
    var dynamicThreshold = (this.kGradientThreshold * stdDev + mean) * Math.sqrt(0.5);
        
    // Find pupil       
    var count = 0;
    var currX = 0;
    var currY = 0;
    var currV = 0;
    for(let y = 0; y < height; y++) {
        for(let x = 0; x < width; x++) {
            let offset = (y * width) + x;
            if(gradientsID.data[offset * 4 + 2] < dynamicThreshold) {
                gradientsID.data[offset * 4 + 4] = 0.0;
                continue;
            }
            
            // Normalize gradient
            var gX = gradientsID.data[offset * 4 + 0] - 128.0;
            var gY = gradientsID.data[offset * 4 + 1] - 128.0;
            
            var magn = Math.sqrt(gX * gX + gY * gY);
    
            gX /= magn;
            gY /= magn;
            
            for(let cy = 0; cy < height; cy++) {
                for(let cx = 0; cx < width; cx++) {
                    if(cx == x && cy == y) continue;
                    var coffset = cy * width + cx;
                    var dx = (x - cx)|0;
                    var dy = (y - cy)|0;
                    var m = Math.sqrt(dx * dx + dy * dy);
                    dx /= m;
                    dy /= m;
                    
                    var d = dx * gX + dy * gY;
                    
                    if(d <= 0) continue;
                                            
                    this.pPupil[coffset] += d * d * (255.0 - blurredID.data[coffset * 4]);
                }
            }
            
            if(this.pPupil[offset] > currV) {
                currX = x;
                currY = y;
                currV = this.pPupil[offset];
            }
        }
    }  
        
    // Convert back in window coordinates
    currX = ROI[0] + currX / width * ROI[2];
    currY = ROI[1] + currY / height * ROI[3];
    
    // Draw to context
    if(this._context !== undefined)
        gradientsI.drawToContext2D(this._context);
    
    gradientsI.release();
    croppedI.release();
    blurredI.release();

    gradients.release();
    cropped.release();
    blurred.release();
    
    this.pupil[0] = currX;
    this.pupil[1] = currY;
    
    return this.pupil;
}