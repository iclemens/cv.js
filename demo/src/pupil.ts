import { Observable } from 'rxjs/Observable';

import 'rxjs/add/observable/interval';

import 'rxjs/add/operator/map';
import 'rxjs/add/operator/sample';
import 'rxjs/add/operator/share';

import { Image } from '@iclemens/cv';
import { fromCamera } from '@iclemens/rxcv';
import { CanvasSink } from '@iclemens/rxcv';

import { ScalePyramid } from '@iclemens/cv';

import * as CV from '@iclemens/cv';

// Functions from haar.js
declare function drawCentre(context, x, y): void;
declare function drawRects(context, rects, color): void;

// Functions from pupil.js
declare function PupilDetector(CV, context): void;
declare function FaceAndEyeDetector(CV): void;


const retain = (count: number) => {
    return function(image) {
        for(let i = 0; i < count; i++) {
            image.retain();
        }
    }
};

// Setup camera
const cameraSource = fromCamera().share().sample(Observable.interval(50));

// Setup contexts for feature overlays
const feature_canvas_id = 'features';
const feature_canvas = <HTMLCanvasElement> document.getElementById(feature_canvas_id);
const feature_context = feature_canvas.getContext('2d');

// Setup canvas for video output
const video_canvas_id = 'video';
const video_canvas = <HTMLCanvasElement> document.getElementById(video_canvas_id);
const video_canvas_sink = new CanvasSink(video_canvas);

const eyeL_canvas = <HTMLCanvasElement> document.getElementById('eyeL');
const eyeR_canvas = <HTMLCanvasElement> document.getElementById('eyeR');

const eyeL_context = eyeL_canvas.getContext('2d');
const eyeR_context = eyeR_canvas.getContext('2d');

const grayscale_image = cameraSource.split(0).do(retain(1));

const feDetector = new FaceAndEyeDetector(CV);
const pDetectorL = new PupilDetector(CV, eyeL_context);
const pDetectorR = new PupilDetector(CV, eyeR_context);

grayscale_image.subscribe((image: Image) => {
    const clsrects = feDetector.findFaces(image);

    if (clsrects.length === 0) {
        // Estimate location of head?
        return;
    }

    // Define ROI where eyes should be
    const w = clsrects[0][2];
    const h = clsrects[0][3];

    const clseyes = [[
        clsrects[0][0] + 0.13 * w,
        clsrects[0][1] + 0.25 * w,
        0.35 * w,
        0.30 * h,
    ], [
        clsrects[0][0] + w - (0.13 + 0.35) * w,
        clsrects[0][1] + 0.25 * w,
        0.30 * w,
        0.30 * h,
    ]];

    const pupilL = pDetectorL.findPupil(image, clseyes[0]);
    const pupilR = pDetectorR.findPupil(image, clseyes[1]);

    feature_context.clearRect(0, 0, feature_canvas.width, feature_canvas.height);
    drawRects(feature_context, clsrects, 'blue');
    drawRects(feature_context, clseyes, 'red');

    drawCentre(feature_context, pupilL[0], pupilL[1]);
    drawCentre(feature_context, pupilR[0], pupilR[1]);

    image.release();
});


// Resize canvas on new video frame
cameraSource.subscribe(video_canvas_sink);

cameraSource.subscribe((image: Image) =>
{
    if (feature_canvas.width !== video_canvas_sink.element.width ||
        feature_canvas.height !== video_canvas_sink.element.height)
    {
        feature_canvas.width = video_canvas_sink.element.width;
        feature_canvas.height = video_canvas_sink.element.height;
    }
});
