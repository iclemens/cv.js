import { Observable } from 'rxjs/Observable'
import 'rxjs/add/operator/share'

import { Image } from '@iclemens/cv'
import { CameraCapture } from '@iclemens/rxcv'
import { CanvasSink } from '@iclemens/rxcv'
import { Grayscale } from '@iclemens/rxcv'
import { Blur } from '@iclemens/rxcv'
import { Scale } from '@iclemens/rxcv'
import { FAST } from '@iclemens/rxcv'
import { BRISK } from '@iclemens/rxcv'

// Input and transform objects
var cameraCapture = new CameraCapture();
var grayscale = new Grayscale();
var blur = new Blur();

// Request image width following specifications
var constraints: MediaStreamConstraints = {
    video: { width: 640 }
};

// Open camera and grayscale image
var cameraSource = cameraCapture.Source(undefined, constraints).share();
var sharedInput = grayscale.Process(cameraSource).share();

// Setup contexts for feature overlays
var feature_canvas_ids = ['features'];
var feature_canvases = [];
var feature_contexts = [];

for(var i = 0; i < feature_canvas_ids.length; i++) {
    feature_canvases.push(document.getElementById(feature_canvas_ids[i]));
    feature_contexts.push(feature_canvases[i].getContext("2d"));
}

// Setup canvas for video output
var video_canvas_ids = ['video'];
var video_canvas_sinks = [];
var video_canvases = [];

for(var i = 0; i < video_canvas_ids.length; i++) {
    video_canvas_sinks[i] = new CanvasSink();
    video_canvas_sinks[i].element = document.getElementById(video_canvas_ids[i]);
}

// Make feature canvas the same size as the video canvas
video_canvas_sinks[0].Process(cameraSource).subscribe(function() {
    feature_canvases[0].width = video_canvas_sinks[0].element.width;
    feature_canvases[0].height = video_canvas_sinks[0].element.height;
});

// Setup scaled versions of pipeline
for(var i = 0; i < 1; i++) {
    (function() {
        var scaleFactor = 1.0 / Math.pow(2.0, i);

        var scale = new Scale();
        scale.setScale(scaleFactor);

        /*var fast = new FAST();
        fast.setS(12);
        fast.setT(15);
        fast.setNonMaxSupp(false);*/

        var fast = new BRISK();
        fast.T = 50.0;
        fast.octaveCount = 5.0;
        
        var scaledInput = scale.Process(sharedInput);            
        
        fast.Process(sharedInput).subscribe(function(f) {          
            for(var i = 0; i < f.length; i++) {
                feature_contexts[0].beginPath();
                feature_contexts[0].arc(f[i].x / scaleFactor, f[i].y / scaleFactor, 5, 0, 2.0 * Math.PI, false);
                feature_contexts[0].lineWidth = 1;
                
                if(scaleFactor == 1.0)
                    feature_contexts[0].strokeStyle = 'red';
                else
                    feature_contexts[0].strokeStyle = 'blue';
                feature_contexts[0].stroke();
            }            
        });
    
    }());
}
