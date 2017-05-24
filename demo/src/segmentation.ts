import { Observable } from 'rxjs/Observable'
import 'rxjs/add/operator/share'
import 'rxjs/add/observable/combineLatest'

import { Image } from '@iclemens/cv'
import { CameraCapture } from '@iclemens/rxcv'
import { CanvasSink } from '@iclemens/rxcv'
import { Grayscale } from '@iclemens/rxcv'
import { Blur } from '@iclemens/rxcv'
import { Scale } from '@iclemens/rxcv'
import { FAST } from '@iclemens/rxcv'
import { BRISK } from '@iclemens/rxcv'
import { Canny } from '@iclemens/rxcv'

declare function algorithm0(pointCloud);
declare function widestGap(M);
declare function mSegmentation(M, w);
declare function triangulate(pointCloud)


var cameraCapture = new CameraCapture();

// Request image width following specifications
var constraints: MediaStreamConstraints = {
    video: { width: 640 }
};

// Open camera and grayscale image
var cameraSource = cameraCapture.Source(undefined, constraints).share();

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


var sharedInput = grayscale.Process(cameraSource).share();

video_canvas_sinks[0].Process(cameraSource).subscribe(function() {
    feature_canvases[0].width = video_canvas_sinks[0].element.width;
    feature_canvases[0].height = video_canvas_sinks[0].element.height;
});

var scales = [1.0/2.0, 1.0/4.0, 1.0/8.0, 1.0/16.0, 1.0/32.0];
var scalers = [];
var featureDetectors = [];
var featureObservables = [];

// Setup scaled versions of pipeline
/*for(var i = 0; i < scales.length; i++) {
    let scale = scales[i];
    scalers[i] = new Scale();
    scalers[i].setScale(scales[i]);

    featureDetectors[i] = new FAST();
    featureDetectors[i].setS(12);
    featureDetectors[i].setT(15);
    featureDetectors[i].setNonMaxSupp(false);

    featureObservables[i] = featureDetectors[i]
        .Process(scalers[i].Process(sharedInput))
        .map(
            function(features) {
                features.forEach(element => {
                    element.x /= scale;
                    element.y /= scale;
                });
                
                return features;
            }
    )   
}*/

var scale = 1.0/8.0;
var scaler = new Scale();
scaler.setScale(scale);

var canny = new Canny();
featureObservables[0] = canny.Process( scaler.Process(sharedInput) ).map((image): any => {
    var image_data = image.asImageData();
    var data = image_data.getUint8Array();

    var w = image_data.width;
    var h = image_data.height;
    var points: any[] = [];

    for(var x = 0; x < w; x++) {
        for(var y = 0; y < h; y++) {
            if(data[x * 4 + y * w * 4 + 2] == 255)
                points.push({x: x/scale, 
                    y: y/scale})
        }
    }

    image_data.release();
    image.release();

    return points;
});


Observable.combineLatest(featureObservables).subscribe(function(features) {
    var pointCloud = [];

    for(var i = 0; i < features.length; i++) {
        for(var j = 0; j < features[i].length; j++) {
            var feature = features[i][j];          
            pointCloud.push([feature.x, feature.y]);
        }
    }

    var M = algorithm0(pointCloud);      
    var w = widestGap(M);
    var Mp = mSegmentation(M, w.pointsAbove);

    var triangles = triangulate(pointCloud);

    var colors = ["rgba(0, 255, 0, 0.8)", "rgba(255, 0, 0, 0.8)", "rgba(0, 0, 255, 0.8)", "rgba(255, 0, 255, 0.8)"];

    for(var s = 1; s < Mp.length; s++) {
        for(var t = 0; t < Mp[s].core.length; t++) {
            var ind = Mp[s].core[t].ind;
            
            if(ind >= triangles.length) continue;
                    
            var c1 = pointCloud[triangles[ind][0]];
            var c2 = pointCloud[triangles[ind][1]];
            var c3 = pointCloud[triangles[ind][2]];
            
            feature_contexts[0].beginPath();
            feature_contexts[0].moveTo(c1[0], c1[1]);
            feature_contexts[0].lineTo(c2[0], c2[1]);
            feature_contexts[0].lineTo(c3[0], c3[1]);
            feature_contexts[0].fillStyle = colors[(s - 1) % colors.length];
            feature_contexts[0].fill();
        }
    }
});