import { Observable } from 'rxjs/Observable'
import 'rxjs/add/operator/share'
import 'rxjs/add/operator/map'
import 'rxjs/add/operator/sample'
import 'rxjs/add/observable/interval'

import { Image } from '@iclemens/cv'
import { CameraCapture } from '@iclemens/rxcv'
import { CanvasSink } from '@iclemens/rxcv'
import { Grayscale } from '@iclemens/rxcv'
import { Blur } from '@iclemens/rxcv'
import { Scale } from '@iclemens/rxcv'
import { Split } from '@iclemens/rxcv'
import { BRISK } from '@iclemens/rxcv'
import { ScalePyramid } from '@iclemens/cv'

import * as CV from '@iclemens/cv'

// Functions from haar.js
declare function drawCentre(context, x, y): void;
declare function drawRects(context, rects, color): void;

// Functions from pupil.js
declare function PupilDetector(CV, context): void;
declare function FaceAndEyeDetector(CV): void;


var retain = function(count) {
    return function(image) {
        for(let i = 0; i < count; i++) {
            image.retain();
        }
    }
}

// Setup camera    
var cameraSource = new CameraCapture().Source().share().sample(Observable.interval(50));

// Setup contexts for feature overlays
var feature_canvas_id = 'features';
var feature_canvas = <HTMLCanvasElement> document.getElementById(feature_canvas_id);
var feature_context = feature_canvas.getContext('2d');

// Setup canvas for video output
var video_canvas_id = 'video';
var video_canvas_sink = new CanvasSink();
var video_canvas = <HTMLCanvasElement> document.getElementById(video_canvas_id);
video_canvas_sink.element = video_canvas;

var eyeL_canvas = <HTMLCanvasElement> document.getElementById('eyeL');
var eyeR_canvas = <HTMLCanvasElement> document.getElementById('eyeR');

var eyeL_context = eyeL_canvas.getContext('2d');
var eyeR_context = eyeR_canvas.getContext('2d');

var grayscale = new Split(0);
var grayscale_image = grayscale.Process(cameraSource).do(retain(1));

var feDetector = new FaceAndEyeDetector(CV);
var pDetectorL = new PupilDetector(CV, eyeL_context);
var pDetectorR = new PupilDetector(CV, eyeR_context);

grayscale_image.subscribe(function(image) {
    var clsrects = feDetector.findFaces(image);
    
    if(clsrects.length == 0) {
        // Estimate location of head?
        return;
    }

    // Define ROI where eyes should be        
    var w = clsrects[0][2];
    var h = clsrects[0][3];
    
    var clseyes = [[
        clsrects[0][0] + 0.13 * w,
        clsrects[0][1] + 0.25 * w,
        0.35 * w,
        0.30 * h 
    ], [
        clsrects[0][0] + w - (0.13 + 0.35) * w,
        clsrects[0][1] + 0.25 * w,
        0.30 * w,
        0.30 * h 
    ]];
    
    var pupilL = pDetectorL.findPupil(image, clseyes[0]);
    var pupilR = pDetectorR.findPupil(image, clseyes[1]);
    
    feature_context.clearRect(0, 0, feature_canvas.width, feature_canvas.height);
    drawRects(feature_context, clsrects, 'blue');
    drawRects(feature_context, clseyes, 'red');
    
    drawCentre(feature_context, pupilL[0], pupilL[1]);
    drawCentre(feature_context, pupilR[0], pupilR[1]);
    
    image.release();
});


// Resize canvas on new video frame
video_canvas_sink.Process(cameraSource).subscribe(function(image) 
{
    if(feature_canvas.width != video_canvas_sink.element.width ||
        feature_canvas.height != video_canvas_sink.element.height)
    {   
        feature_canvas.width = video_canvas_sink.element.width;
        feature_canvas.height = video_canvas_sink.element.height;
    }
});       
