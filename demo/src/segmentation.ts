import { Observable, combineLatest } from 'rxjs';

import { share, map } from 'rxjs/operators';

import { Image } from '@iclemens/cv';
import { fromCamera } from '@iclemens/rxcv';
import { CanvasSink } from '@iclemens/rxcv';
import { scale, grayscale, sobel } from '@iclemens/rxcv';

declare function algorithm0(pointCloud);
declare function widestGap(M);
declare function mSegmentation(M, w);
declare function triangulate(pointCloud);

// Request image width following specifications
const constraints: MediaStreamConstraints = {
    video: { width: 640 },
};

// Open camera and grayscale image
const cameraSource = fromCamera(constraints).pipe(share());

// Setup contexts for feature overlays
const featureCanvasIds = ['features'];
const feature_canvases = [];
const feature_contexts = [];

for (let i = 0; i < featureCanvasIds.length; i++) {
    feature_canvases.push(document.getElementById(featureCanvasIds[i]));
    feature_contexts.push(feature_canvases[i].getContext('2d'));
}

// Setup canvas for video output
const videoCanvasIds = ['video'];
const video_canvas_sinks = [];
const video_canvases = [];

for (let i = 0; i < videoCanvasIds.length; i++) {
    video_canvas_sinks[i] = new CanvasSink(document.getElementById(videoCanvasIds[i]) as HTMLCanvasElement);
}

cameraSource.subscribe(video_canvas_sinks[0]);

cameraSource.subscribe(() => {
    feature_canvases[0].width = video_canvas_sinks[0].element.width;
    feature_canvases[0].height = video_canvas_sinks[0].element.height;
});

const featureObservables = [];
const scale_factor = 1.0 / 4.0;
const inputImage: Observable<Image> = cameraSource.pipe(scale(scale_factor), grayscale(), sobel());

featureObservables[0] = inputImage.pipe(map((image): any => {
    const image_data = image.asImageData();
    const data = image_data.getUint8Array();

    const w = image_data.width;
    const h = image_data.height;
    const points: any[] = [];

    for (let x = 20; x < w - 20; x++) {
        for (let y = 20; y < h - 20; y++) {
            if (data[x * 4 + y * w * 4] > 100 || data[x * 4 + y * w * 4 + 1] > 100) {
                points.push({x: x / scale_factor, y: y / scale_factor});
            }
        }
    }

    image_data.release();
    image.release();

    return points;
}));


combineLatest(featureObservables).subscribe((features) => {
    const pointCloud = [];

    for (let i = 0; i < features.length; i++) {
        for (let j = 0; j < features[i].length; j++) {
            const feature = features[i][j];
            pointCloud.push([feature.x, feature.y]);
        }
    }

    const M = algorithm0(pointCloud);
    const w = widestGap(M);

    if (w === undefined) { return; }

    const Mp = mSegmentation(M, w.pointsAbove);
    const triangles = triangulate(pointCloud);
    const colors = ['rgba(0, 255, 0, 0.8)', 'rgba(255, 0, 0, 0.8)', 'rgba(0, 0, 255, 0.8)', 'rgba(255, 0, 255, 0.8)'];

    for (let s = 1; s < Mp.length; s++) {
        for (let t = 0; t < Mp[s].core.length; t++) {
            const ind = Mp[s].core[t].ind;

            if (ind >= triangles.length) { continue; }

            const c1 = pointCloud[triangles[ind][0]];
            const c2 = pointCloud[triangles[ind][1]];
            const c3 = pointCloud[triangles[ind][2]];

            feature_contexts[0].beginPath();
            feature_contexts[0].moveTo(c1[0], c1[1]);
            feature_contexts[0].lineTo(c2[0], c2[1]);
            feature_contexts[0].lineTo(c3[0], c3[1]);
            feature_contexts[0].fillStyle = colors[(s - 1) % colors.length];
            feature_contexts[0].fill();
        }
    }
});
