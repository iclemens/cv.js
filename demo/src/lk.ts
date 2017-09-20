import { Observable } from 'rxjs/Observable';

import 'rxjs/add/operator/map';
import 'rxjs/add/operator/share';

import { Image } from '@iclemens/cv';
import { LK } from '@iclemens/cv';
import { ScalePyramid } from '@iclemens/cv';

import { fromCamera } from '@iclemens/rxcv';
import { CanvasSink } from '@iclemens/rxcv';
import * as $ from 'jquery';

function fillPyramid(pyramid: ScalePyramid, image: Image, Lm: number): Image[]
{
    pyramid.buildPyramid(image, Lm);
    return pyramid.asImages();
}

/**
 * Function that returns a sequence of tuples, each
 *  containing both the last and the current image tree.
 */
function history(source: Observable<Image>): Observable<Image[][]>
{
    let count = 0;
    const images = [[], []];

    const pyramids = [
        new ScalePyramid(),
        new ScalePyramid(),
    ];

    return source.map((current) => {
        let result: Image[][] = [];

        if (count === 0) {
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


// Request image width following specifications
const constraints: MediaStreamConstraints = {
    video: { width: 640 },
};

// Open camera and grayscale image
const cameraSource$ = fromCamera(constraints).share();

// Setup contexts for feature overlays
const featureCanvasId = 'features';
const featureCanvas: HTMLCanvasElement = document.getElementById(featureCanvasId) as HTMLCanvasElement;

if (featureCanvas === undefined) {
    throw new Error('Could not find canvas');
}

const featureContext = featureCanvas.getContext('2d');

if (featureContext === undefined) {
    throw new Error('Unable to obtain 2D context');
}

// Setup canvas for video output
const videoCanvasId = 'video';
const videoCanvasSink = new CanvasSink(document.getElementById(videoCanvasId) as HTMLCanvasElement);

const lk = new LK(0);

const sharedInput = cameraSource$.grayscale().share();
let currentFeatures = [];

function plot_feature(feature, color)
{
    featureContext.beginPath();
    featureContext.arc(feature.x, feature.y,
        5.0, 0.0, 2.0 * Math.PI, false);
    featureContext.strokeStyle = color;
    featureContext.lineWidth = 1.0;
    featureContext.stroke();
    featureContext.closePath();
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

const pointBuffer = [];

history(sharedInput).subscribe((images) => {
    if (currentFeatures.length < 1) {
        return;
    }

    const next = lk.calcOpticalFlowPyrLK(images[0], images[1], currentFeatures, 5, 3);
    console.log(next.nextPts[0]);
    currentFeatures[0] = next.nextPts[0];

    pointBuffer.push(next.nextPts[0]);

    if (pointBuffer.length > 15) { pointBuffer.shift(); }

    featureContext.clearRect(0, 0, featureCanvas.width, featureCanvas.height);

    for (const point of pointBuffer) {
        plot_feature(point, '#0000FF');
    }
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

featureCanvas.addEventListener('click', (event) => {
    /**
     * This resets the feature, but should
     * add to the list instead.
     */
    const offset = $(featureCanvas).offset();

    currentFeatures = [{
        x: event.pageX - offset.left,
        y: event.pageY - offset.top,
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

cameraSource$.subscribe(videoCanvasSink);

cameraSource$.subscribe(() => {
    if (featureCanvas.width !== videoCanvasSink.element.width ||
        featureCanvas.height !== videoCanvasSink.element.height) {
        featureCanvas.width = videoCanvasSink.element.width;
        featureCanvas.height = videoCanvasSink.element.height;
    }
});
