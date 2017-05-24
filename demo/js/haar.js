

function drawCentre(context, x, y)
{
    context.beginPath();
    context.moveTo(x - 5, y);
    context.lineTo(x + 5, y);
    
    context.moveTo(x, y - 5);
    context.lineTo(x, y + 5);
    //context.arc(x, y, 3, 0, 2.0 * Math.PI);
    context.strokeStyle = 'red';
    context.stroke();
}


function drawRects(context, rects, color) {
    for(var i = 0; i < rects.length; i++) {
        var rect = rects[i];
        
        context.beginPath();
        context.rect(rect[0], rect[1], rect[2], rect[3]);
        context.lineWidth = 1;
        context.strokeStyle = color;
        context.stroke();
    }
}


function scaleRect(rect, scale) {
    srect = [rect[0], rect[1], rect[2], rect[3]];
    
    for(var i = 0; i < rect.length; i++) {
        srect[i] = srect[i] * scale;
    }
    
    return srect;
}

function scaleRectsInPlace(rects, scale)
{
    for(var i = 0; i < rects.length; i++) {
        for(var j = 0; j < 4; j++) {
            rects[i][j] *= scale;
        }
    }
}

/******************
 * CascadeWrapper *
 ******************/

function CascadeWrapper(CV, cascade)
{
    this._CV = CV;
    this._cascade = cascade;
    this._classifier = new CV.HaarClassifier(cascade);
    this._cascadeArea = this._classifier.width * this._classifier.height;
}

CascadeWrapper.prototype.suggestScales = function(image)
{
    var scales = this._CV.GetHaarScales(this._cascade, image.width, image.height);
    return scales;
}


/**
 * First we detect faces in the lower scales (1/16 and 1/32).
 * Then we create the following record for every face:
 *   imageIdx, scaleEst, minX, maxX, minY, maxY
 * Where the min and max are derived from the x-value +/- a
 *   fraction of the width of the detected face (e.g. 10%).
 * Then we moved from imageIdx downto 1, we detect faces at
 *   every imageIdx (should we search around the estimated scale?).
 * When we reach imageIdx == 1, we do not only group but also apply
 *   the minimum number of rectangles crit. to remove
 *   unwanted "faces".
 */

CascadeWrapper.prototype.matchScaleWithPyramid = function(pyramid, minBaseImage)
{
    var images = pyramid.asImages();
    var requiredScales = this.suggestScales(images[0]);
    var scaleFactors = pyramid.scaleFactors;

    // Match every scale with an image in our scale pyramid.
    if(minBaseImage === undefined) minBaseImage = 1;
    
    var minPixels = 100;
    var scales = [];
    
    for(var i = 0; i < requiredScales.length; i++) {
        for(var j = scaleFactors.length - 1; j >= 0; j--) {
            var ratio = requiredScales[i] / (1 / scaleFactors[j]);
                        
            if(ratio >= 1) break;
        }
        
        j = Math.max(minBaseImage, j);
        ratio = requiredScales[i] / (1 / scaleFactors[j]);
        
        var pixels = Math.floor(this._cascadeArea * (ratio * ratio));
        if(pixels < minPixels) continue;
                    
        scales.push([i, requiredScales[i], j, scaleFactors[j], ratio]);
    }
    
    scales.sort(function(a, b) {
        return a[0] > b[0];
    });
    
    return scales;
}


CascadeWrapper.prototype.findObjectsInArea = function(image, imageScale, cascadeScale, minX, maxX, minY, maxY)
{
    this._classifier.scale = cascadeScale;
    this._classifier.setImage(image);
    
    var stepX = Math.min(1.0, Math.floor(cascadeScale * 1.5));
    var stepY = Math.min(1.0, Math.floor(cascadeScale * 1.5));
    
    var objects = this._classifier.detectObject(minX, maxX, minY, maxY, stepX, stepY);
    scaleRectsInPlace(objects, 1.0 / imageScale);
    
    return objects;
}


/**
 * Returns an array of detected object positions
 * as if they were detected in the original image.
 */
CascadeWrapper.prototype.findObjects = function(image, imageScale, cascadeScale)
{
    this._classifier.scale = cascadeScale;
    this._classifier.setImage(image);
    
    var objects = this._classifier.detectObject();
    
    for(var i = 0; i < objects.length; i++) {
        for(var j = 0; j < 4; j++) {
            objects[i][j] /= imageScale;
        }
    }
    
    return objects;        
}


CascadeWrapper.prototype.findObjectsMultiscale = function(scalePyramid, ROI, minScale, maxScale)
{
    var images = scalePyramid.asImages();
    var imageScales = scalePyramid.scaleFactors;
    
    // If no ROI is specified, search whole image
    if(ROI === undefined)
        ROI = [0, images[0].width, 0, images[0].height];
    
    if(minScale === undefined)
        minScale = images.length - 1;
    else
        minScale = Math.min(images.length - 1, minScale);
        
    if(maxScale === undefined)
        maxScale = 0;
    else
        maxScale = Math.max(0, maxScale);
    
    // Determine the scales at which to scan the ROI
    var cascadeScales = this.suggestScales({ width: ROI[1], height: ROI[3] });
    
    var objectsToInvestigate = [];
        
    for(let i = minScale; i >= maxScale; i--)
    {
        var maxDim = (ROI[1] - ROI[0]) * imageScales[i];
        if(maxDim < 150) {
            for(let j = 0; j < cascadeScales.length; j++) {
                var ratio = cascadeScales[j] * imageScales[i];
                
                if(ratio > 0.8) {
                    objectsToInvestigate.push([ratio, 
                        Math.round(ROI[0] * imageScales[i]), 
                        Math.round(ROI[1] * imageScales[i]),
                        Math.round(ROI[2] * imageScales[i]),
                        Math.round(ROI[3] * imageScales[i])]);
                    cascadeScales[j] = undefined;
                }
            }
        }
        
        var objects = [];
        
        // Scan for faces in the regions specified
        for(let j = 0; j < objectsToInvestigate.length; j++) {
            var localObjects = this.findObjectsInArea(images[i], 
                imageScales[i], objectsToInvestigate[j][0],
                objectsToInvestigate[j][1], objectsToInvestigate[j][2],
                objectsToInvestigate[j][3], objectsToInvestigate[j][4]);
         
            objects = Array.prototype.concat(objects, localObjects);
        }
              
        if(i == maxScale) {
            return this._CV.groupRectangles(objects, 0.2, 3.0);
        }
        
        // Group objects
        objects = this._CV.groupRectangles(objects, 0.2, 1.0);        
        
        objectsToInvestigate = [];
        
        for(let j = 0; j < objects.length; j++) {
            var x = Math.round(objects[j][0] * imageScales[i - 1]);
            var y = Math.round(objects[j][1] * imageScales[i - 1]);
            
            var cascadeScale = objects[j][2] / this._classifier._cascade.size[0];
            var ratio = cascadeScale * imageScales[i - 1];
                        
            var xd = 10;
            var yd = 10;
            
            objectsToInvestigate.push([ratio, x - xd, x + xd, y - yd, y + yd]);
        }
    }
    
}


/**********************
 * FaceAndEyeDetector *
 **********************/

function FaceAndEyeDetector(CV)
{
    this._CV = CV;
    
    this.faceClassifier = new CascadeWrapper(CV, CV.HaarCascadeFrontalFaceAlt);
    this.eyeClassifier = new CascadeWrapper(CV, CV.HaarCascadeEye);    
    this.scalePyramid = new CV.ScalePyramid();
}


FaceAndEyeDetector.prototype.findEyes = function(image, ROIrect)
{   
    // Area in which to search for the eyes
    var ROI = [ROIrect[0], ROIrect[0] + ROIrect[2], 
               ROIrect[1], ROIrect[1] + ROIrect[3]];
    
    return this.eyeClassifier.findObjectsMultiscale(this.scalePyramid, ROI, 3, 2);
}


FaceAndEyeDetector.prototype.findFaces = function(image) {
    // Build scale pyramid, aiming for a specific number of pixels.
    this.scalePyramid.buildPyramid(image, 6.0);        

    // FIXME: Find a way to share the IntegralImages e.g. using an
    // IntegralImageScalePyramid.

    return this.faceClassifier.findObjectsMultiscale(this.scalePyramid, undefined, undefined, 2);
}
