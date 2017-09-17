import { Observable } from 'rxjs/Observable';

import 'rxjs/add/operator/share';

import { CanvasSink } from '@iclemens/rxcv';
import { CameraCapture } from '@iclemens/rxcv';

const cameraCapture = new CameraCapture();

// Setup contexts for feature overlays
const featureCanvasIds = ['features'];
const featureCanvases = [];
const featureContexts = [];

for (let i = 0; i < featureCanvasIds.length; i++) {
    featureCanvases.push(document.getElementById(featureCanvasIds[i]));
    featureContexts.push(featureCanvases[i].getContext('2d'));
}

// Setup canvas for video output
const videoCanvasIds = ['video'];
const videoCanvasSinks = [];

for (let i = 0; i < videoCanvasIds.length; i++) {
    videoCanvasSinks[i] = new CanvasSink();
    videoCanvasSinks[i].element = document.getElementById(videoCanvasIds[i]);
}

const cameraSource = cameraCapture.Source().share();

videoCanvasSinks[0].Process(cameraSource.grayscale().sobel()).subscribe(() => {
    featureCanvases[0].width = videoCanvasSinks[0].element.width;
    featureCanvases[0].height = videoCanvasSinks[0].element.height;
});
