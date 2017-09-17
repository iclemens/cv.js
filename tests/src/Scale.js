define(['QUnit', 'tests/Utilities', 'rxjs', '@iclemens/cv', '@iclemens/rxcv'], function(QUnit, Utilities, Rx, CV, RxCV)
{
    return {
        "run": function() {
            function test_scale(assert, s, name)
            {
                var done = assert.async();

                const referenceImage = new RxCV.LoadImage();
                referenceImage.url = "reference/lab.grayscale." + name + ".png";
                const referenceImage$ = referenceImage.Generate();

                var originalImage = new RxCV.LoadImage();
                originalImage.url = "reference/lab.grayscale.png";
                const originalImage$ = originalImage.Generate();

                const scaleImage$ = originalImage$.scale(s, s);

                Rx.Observable.combineLatest([referenceImage$, scaleImage$]).subscribe(function(images) {
                    var originalI = images[1].asImageData();
                    var referenceI = images[0].asImageData();
                    
                    var original = originalI.getImageData();
                    var reference = referenceI.getImageData();

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
                    
                    originalI.release();
                    referenceI.release();
                });
            }

            QUnit.test("Scaling (1/2)", function(assert) { return test_scale(assert, 0.5, 'half'); });
            QUnit.test("Scaling (2/3)", function(assert) { return test_scale(assert, 2.0/3.0, 'twothird'); });    
        }
    }
});