import { Observable } from 'rxjs';

import { share } from 'rxjs/operators';

import { Image } from '@iclemens/cv';
import { fromCamera } from '@iclemens/rxcv';
import { CanvasSink } from '@iclemens/rxcv';
import { grayscale, scale, fast } from '@iclemens/rxcv';

// Request image width following specifications
const constraints: MediaStreamConstraints = {
    video: { width: 640 },
};

// Open camera and grayscale image
const camera$ = fromCamera(constraints).pipe(share());
const sharedInput: Observable<Image> = camera$.pipe(grayscale(), share());

// Setup contexts for feature overlays
const featureCanvasIds = ['features'];
const featureCanvases = [];
const featureContexts = [];

for (let i = 0; i < featureCanvasIds.length; i++) {
    featureCanvases.push(document.getElementById(featureCanvasIds[i]));
    featureContexts.push(featureCanvases[i].getContext('2d'));
}

// Setup canvas for video output
const videoCanvasIds = ['video', 'video2'];
const videoCanvasSinks: CanvasSink[] = [];

for (const id of videoCanvasIds) {
    videoCanvasSinks.push(new CanvasSink(document.getElementById(id) as HTMLCanvasElement));
}

camera$.subscribe(videoCanvasSinks[0]);

// Make feature canvas the same size as the video canvas
camera$.subscribe(() => {
    featureCanvases[0].width = videoCanvasSinks[0].element.width;
    featureCanvases[0].height = videoCanvasSinks[0].element.height;
});

// Setup scaled versions of pipeline
for (let i = 1; i < 2; i++) {
    (() => {
        const scaleFactor = 1.0 / Math.pow(2.0, i);

        const scaledInput = sharedInput.pipe(scale(scaleFactor));

        scaledInput.pipe(fast(undefined, 50.0, 5.0)).subscribe((f) => {
            for (const j of f) {
                featureContexts[0].beginPath();
                featureContexts[0].arc(j.x / scaleFactor, j.y / scaleFactor, 5, 0, 2.0 * Math.PI, false);
                featureContexts[0].lineWidth = 1;

                if (scaleFactor === 1.0) {
                    featureContexts[0].strokeStyle = 'red';
                } else {
                    featureContexts[0].strokeStyle = 'blue';
                }
                featureContexts[0].stroke();
            }
        });

    })();
}
