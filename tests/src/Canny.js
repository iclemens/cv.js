define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            QUnit.test("Canny", function(assert) {

                var done = assert.async();

                var referenceImage = new RxCV.LoadImage();
                referenceImage.url = 'reference/canny/lab.grayscale.canny.t100.t200.ap3.false.png';
                const referenceImage$ = referenceImage.Generate();

                var originalImage = new RxCV.LoadImage();
                originalImage.url = 'reference/lab.grayscale.png';
                const originalImage$ = originalImage.Generate();

                const cannyImage$ = originalImage$.pipe(RxCV.canny(100.0, 200.0));
                
                Rx.combineLatest([referenceImage$, cannyImage$]).subscribe(function(images) {
                    var original = images[1].asImageData().getImageData();
                    var reference = images[0].asImageData().getImageData();

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