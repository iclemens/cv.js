import { Observable } from 'rxjs/Observable'
import 'rxjs/add/operator/share'
import 'rxjs/add/operator/map'

import { Image } from '@iclemens/cv'
import { CameraCapture } from '@iclemens/rxcv'
import { CanvasSink } from '@iclemens/rxcv'
import { LK } from '@iclemens/cv'
import { ScalePyramid } from '@iclemens/cv'
import * as $ from 'jquery'

function fillPyramid(pyramid, image, Lm)
{
    pyramid.buildPyramid(image, Lm);
    return pyramid.asImages();
}

/**
 * Function that returns a sequence of tuples, each
 *  containing both the last and the current image tree.
 */
function history(source: Observable<Image>)
{
    var count = 0;
    var images = [[], []];

    var pyramids = [
        new ScalePyramid(),
        new ScalePyramid()
    ];
    
    
    return source.map(function(current) {
        var result = [];
        
        if(count == 0) {
            images[0] = fillPyramid(pyramids[0], current, 4.0);
            count = 1;
            result = [images[1], images[0]];
        } else {
            images[1] = fillPyramid(pyramids[1], current, 4.0);
            count = 0;
            result = [images[0], images[1]];
        }
        
        return result;
    });
} 


var cameraCapture = new CameraCapture();

// Request image width following specifications
var constraints: MediaStreamConstraints = {
    video: { width: 640 }
};

// Open camera and grayscale image
var cameraSource = cameraCapture.Source(undefined, constraints).share();

// Setup contexts for feature overlays
var feature_canvas_id = 'features';
var feature_canvas: HTMLCanvasElement = <HTMLCanvasElement> document.getElementById(feature_canvas_id);

if(feature_canvas === undefined)
    throw "Could not find canvas";

var feature_context = feature_canvas.getContext('2d');

if(feature_context === undefined)
    throw "Unable to obtain 2D context"

// Setup canvas for video output
var video_canvas_id = 'video';
var video_canvas_sink = new CanvasSink();
video_canvas_sink.element = <HTMLCanvasElement> document.getElementById(video_canvas_id);
    
var lk = new LK(0);

var sharedInput = cameraSource.grayscale().share();
var currentFeatures = [];

function plot_feature(feature, color)
{
    feature_context.beginPath();
    feature_context.arc(feature.x, feature.y,
        5.0, 0.0, 2.0 * Math.PI, false);
    feature_context.strokeStyle = color;
    feature_context.lineWidth = 1.0;
    feature_context.stroke();
    feature_context.closePath();
}


/**
 * The problem is that the shared input contains a sequence of the same element
 *  [element, element, element]
 * 
 * The contents of which are always the latest element. It is difficult to
 *  keep the contents over time. We therefore might want to keep the contents
 *  as a texture or as ImageData for future processing. There are two options:
 * 
 * 1) We make an operator that performs this caching step
 * 2) We generate a new input texture from the texture pool every time
 *      and .dispose() that texture after we are finished with it. This
 *      would require us to do a .copy() on .publish() and .dispose() after
 *      every subscribe();
 */

var pointBuffer = [];

history(sharedInput).subscribe(function(images) {
    if(currentFeatures.length < 1) 
        return;
    
    var next = lk.calcOpticalFlowPyrLK(images[0], images[1], currentFeatures, 5, 3);
    console.log(next.nextPts[0]);
    currentFeatures[0] = next.nextPts[0];
    
    pointBuffer.push(next.nextPts[0]);
    
    if(pointBuffer.length > 15) pointBuffer.shift();
    
    feature_context.clearRect(0, 0, feature_canvas.width, feature_canvas.height);
    
    for(var i = 0; i < pointBuffer.length; i++)
        plot_feature(pointBuffer[i], '#0000FF');
});

/*
Rx.Observable.zip(sharedInput.skip(1), sharedInput).subscribe(function(images) {
    if(currentFeatures.length < 1) 
        return;
    
    try {
        var next = lk.calcOpticalFlowPyrLK([images[0]], [images[1]], currentFeatures, 5, 3);
        plot_feature(next.nextPts[0], '#0000FF');
    } catch(e) {
        console.log("Oops", e);
    }
});
*/

feature_canvas.addEventListener('click', function(event) {
    /**
     * This resets the feature, but should
     * add to the list instead.
     */
    var offset = $(feature_canvas).offset();
    
    currentFeatures = [{ 
        x: event.pageX - offset.left,
        y: event.pageY - offset.top
    }];
    
    plot_feature(currentFeatures[0], '#FF0000');
});





/* brisk.Process(sharedInput).subscribe(function(f) {
    if(currentFeatures.length == 0)
        return;
    
    /** Plot current feature *
    console.log(feature_context, currentFeatures);
    feature_context.beginPath();
    feature_context.arc(currentFeatures[0].x, currentFeatures[0].y,
        5.0, 0.0, 2.0 * Math.PI, false);
    feature_context.strokeStyle = '#FF0000';
    feature_context.lineWidth = 1.0;
    feature_context.stroke();
    feature_context.closePath();
});*/

/** LK should have two inputs:
 *   1) image
 *   2) features
 * 
 * Based on the image in frame n - 1
 */

video_canvas_sink.Process(cameraSource).subscribe(function() {
    if(feature_canvas.width != video_canvas_sink.element.width ||
        feature_canvas.height != video_canvas_sink.element.height) {
        feature_canvas.width = video_canvas_sink.element.width;
        feature_canvas.height = video_canvas_sink.element.height;
    }        
});   