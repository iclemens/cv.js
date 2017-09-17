define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], 
    function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            function test_grayscale(assert, imageIn, imageOut) 
            {
                var done = assert.async();

                const referenceImage = new RxCV.LoadImage();
                referenceImage.url = imageOut;
                const referenceImage$ = referenceImage.Generate();

                const originalImage = new RxCV.LoadImage();
                originalImage.url = imageIn;
                const originalImage$ = originalImage.Generate();
                var grayscaleImage$ = originalImage$.grayscale();

                Rx.Observable.combineLatest([referenceImage$, grayscaleImage$]).subscribe(function(images) {                   
                    var originalI = images[1].asImageData();
                    var referenceI = images[0].asImageData();

                    var original = originalI.getImageData();
                    var reference = referenceI.getImageData();

                    assert.notEqual(original, null, "Original image");
                    assert.notEqual(reference, null, "Reference image"); 

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
        
            QUnit.test("Grayscaling 1", function(assert) { test_grayscale(assert, 'reference/img1.png', 'reference/img1.grayscale.png') });
            QUnit.test("Grayscaling 2", function(assert) { test_grayscale(assert, 'reference/grayscale/img1.original.png', 'reference/grayscale/img1.grayscale.png') });
        } 
    }
});