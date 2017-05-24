import { Observable } from 'rxjs/Observable'
import 'rxjs/add/operator/share'

import { CameraCapture } from '@iclemens/rxcv'
import { Grayscale } from '@iclemens/rxcv'
import { Blur } from '@iclemens/rxcv'
import { Sobel }  from '@iclemens/rxcv'
import { CanvasSink } from '@iclemens/rxcv'


var cameraCapture = new CameraCapture();

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

// Setup shared part of the processing pipe-line    
var grayscale = new Grayscale();
var blur = new Blur();
var sobel = new Sobel();

//blur.Process(

var cameraSource = cameraCapture.Source().share();
    

video_canvas_sinks[0].Process(sobel.Process(grayscale.Process(cameraSource))).subscribe(function() {
    feature_canvases[0].width = video_canvas_sinks[0].element.width;
    feature_canvases[0].height = video_canvas_sinks[0].element.height;
});      