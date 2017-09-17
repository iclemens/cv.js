define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            function test_sobel_func(assert, kernel, scale, delta, border) {
                var done = assert.async();

                var referenceImageV = new RxCV.LoadImage();
                referenceImageV.url = 'reference/sobel/lab.grayscale.sobel' 
                  + '.x0.y1' 
                  + '.ks' + kernel + '.sc' + scale + '.dl' + delta 
                  + '.bt' + border + '.png';

                var referenceImageH = new RxCV.LoadImage();
                referenceImageH.url = 'reference/sobel/lab.grayscale.sobel' 
                  + '.x1.y0' 
                  + '.ks' + kernel + '.sc' + scale + '.dl' + delta 
                  + '.bt' + border + '.png';

                referenceImageV = referenceImageV.Generate();
                referenceImageH = referenceImageH.Generate();

                const originalImage = new RxCV.LoadImage();
                originalImage.url = 'reference/lab.grayscale.png';
                const originalImage$ = originalImage.Generate();
                
                const sobelImage$ = originalImage$.sobel(ksize);

                Rx.Observable.combineLatest([referenceImageH, referenceImageV, sobelImage$]).subscribe(function(images) {
                    var originalI = images[2].asImageData();
                    var referenceHI = images[0].asImageData();
                    var referenceVI = images[1].asImageData();

                    var original = originalI.getImageData();
                    var referenceH = referenceHI.getImageData();
                    var referenceV = referenceVI.getImageData();

                    assert.notEqual(images[2], undefined, "Original image");
                    assert.notEqual(images[0], undefined, "Reference image (H)"); 
                    assert.notEqual(images[1], undefined, "Reference image (V)");

                    assert.notEqual(original, undefined, "Pixels of original image");
                    assert.notEqual(referenceH, undefined, "Pixels of reference (H) image");
                    assert.notEqual(referenceV, undefined, "Pixels of reference (V) image");

                    assert.equal(original.width, referenceH.width, "Image width");
                    assert.equal(original.height, referenceH.height, "Image height");
                    assert.equal(original.data.length, referenceH.data.length, "Length of data elements");

                    var result;
                    result = Utilities.compareImages(original, referenceH, [0]);                   
                    assert.equal(result.isIdentical, true, "Correct pixel values (H; " + result.comment + ")");
                    
                    result = Utilities.compareImages(original, referenceV, [1]);
                    assert.equal(result.isIdentical, true, "Correct pixel values (V; " + result.comment + ")");                    
                    
                    done();
                    
                    originalI.release();
                    referenceHI.release();
                    referenceVI.release();
                });
            }
            
            // Only run regular Sobel for now
            var ksizes = [3]; //[-1, 0, 3];
            for(var k = 0; k < ksizes.length; k++) {
              var ksize = '' + ksizes[k];
              QUnit.test("Sobel K" + ksize + ", S1, D0, B0", function(assert) { test_sobel_func(assert, ksize, 1, 0, 0); });            
            }
        }
    }
});