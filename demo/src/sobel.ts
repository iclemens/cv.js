import { Observable } from 'rxjs';

import { share } from 'rxjs/operators';

import { CanvasSink } from '@iclemens/rxcv';
import { fromCamera } from '@iclemens/rxcv';
import { grayscale, sobel } from '@iclemens/rxcv';

// Setup canvas for video output
const videoCanvasIds = ['video'];
const videoCanvasSinks = [];

for (let i = 0; i < videoCanvasIds.length; i++) {
    videoCanvasSinks[i] = new CanvasSink(document.getElementById(videoCanvasIds[i]) as HTMLCanvasElement);
}

const cameraSource = fromCamera().pipe(share());
cameraSource.pipe(grayscale(), sobel()).subscribe(videoCanvasSinks[0]);
