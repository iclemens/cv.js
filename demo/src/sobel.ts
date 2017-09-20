import { Observable } from 'rxjs/Observable';

import 'rxjs/add/operator/share';

import { CanvasSink } from '@iclemens/rxcv';
import { fromCamera } from '@iclemens/rxcv';

// Setup canvas for video output
const videoCanvasIds = ['video'];
const videoCanvasSinks = [];

for (let i = 0; i < videoCanvasIds.length; i++) {
    videoCanvasSinks[i] = new CanvasSink(document.getElementById(videoCanvasIds[i]) as HTMLCanvasElement);
}

const cameraSource = fromCamera().share();
cameraSource.grayscale().sobel().subscribe(videoCanvasSinks[0]);
