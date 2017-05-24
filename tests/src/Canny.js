define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            QUnit.test("Canny", function(assert) {

                var done = assert.async();

                var referenceImage = new RxCV.LoadImage();
                referenceImage.url = 'reference/canny/lab.grayscale.canny.t100.t200.ap3.false.png';
                referenceImage = referenceImage.Generate();

                var originalImage = new RxCV.LoadImage();
                originalImage.url = 'reference/lab.grayscale.png';
                originalImage = originalImage.Generate();

                var canny = new RxCV.Canny();
                canny.lowThreshold = 100.0;
                canny.highThreshold = 200.0;
                var cannyImage = canny.Process(originalImage);
                
                /*var div = document.createElement("div");
                div.style.position = 'absolute';
                div.style.top = 0.0;
                document.body.appendChild(div);
                
                var canvasses = [];
                var sinks = [];
                for(var q = 0; q < 2; q++) {
                    canvasses[q] = document.createElement("canvas");
                    div.appendChild(canvasses[q]);
                    sinks[q] = new RxCV.CanvasSink();
                    sinks[q].element = canvasses[q];
                }
                sinks[0].Process(cannyImage).subscribe(function() { });
                sinks[1].Process(referenceImage).subscribe(function() { });*/
                
                Rx.Observable.combineLatest([referenceImage, cannyImage]).subscribe(function(images) {
                    var original = images[1].asPixelData();
                    var reference = images[0].asPixelData();

                    assert.notEqual(images[1], undefined, "Original image");
                    assert.notEqual(images[0], undefined, "Reference image"); 

                    assert.notEqual(original, undefined, "Pixels of original image");
                    assert.notEqual(reference, undefined, "Pixels of reference image");

                    assert.equal(original.width, reference.width, "Image width");
                    assert.equal(original.height, reference.height, "Image height");
                    assert.equal(original.data.length, reference.data.length, "Length of data elements");

                    result = Utilities.compareImages(original, reference);
                    
                    assert.equal(result.isIdentical, true, "Correct pixel values (" + result.comment + ")");
                    done();
                });

            });
        }
    }
});