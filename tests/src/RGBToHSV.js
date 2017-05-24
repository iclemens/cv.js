define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            function test_rgb_to_hsv(assert, imageIn, imageOut) 
            {
                var done = assert.async();

                var referenceImage = new RxCV.LoadImage();
                referenceImage.url = imageOut;
                referenceImage = referenceImage.Generate();

                var originalImage = new RxCV.LoadImage();
                originalImage.url = imageIn;
                originalImage = originalImage.Generate();

                var rgbToHSV = new RxCV.RGBToHSV();
                var rgbToHSVImage = rgbToHSV.Process(originalImage)

                Rx.Observable.combineLatest([referenceImage, rgbToHSVImage]).subscribe(function(images) {
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
                });
            }
        
            QUnit.test("RGB To HSV 1", function(assert) { test_rgb_to_hsv(assert, 'reference/img1.png', 'reference/rgbtohsv/img1.hsv.png') });
        } 
    }
});