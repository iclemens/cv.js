define(['QUnit', 'Utilities', 'rxjs', '@iclemens/cv', '@iclemens/rxcv'], function(QUnit, Utilities, Rx, CV, RxCV)
{
    return {
        "run": function() {
            function test_pyrdown(assert, layers)
            {
                var done = assert.async();

                var referenceImage = new RxCV.LoadImage();
                referenceImage.url = "reference/pyrdown/img.pyrdown.layer" + layers + ".png";
                referenceImage = referenceImage.Generate().share();

                var originalImage = new RxCV.LoadImage();
                originalImage.url = "reference/pyrdown/img.original.png";
                originalImage = originalImage.Generate();

                var pyrLayer = [];
                for(var i = 0; i < layers; i++) {
                    pyrLayer[i] = new RxCV.PyrDown();
                    pyrLayer[i].setScale(0.5, 0.5);
                    
                    if(i == 0) {
                        pyrLayer[i] = pyrLayer[i].Process(originalImage);                        
                    } else {
                        pyrLayer[i] = pyrLayer[i].Process(pyrLayer[i - 1]);
                    }
                }

                var pyrdownImage = pyrLayer[pyrLayer.length - 1];

                Rx.Observable.combineLatest([referenceImage, pyrdownImage]).subscribe(function(images) {
                    var original = images[1].asPixelData();
                    var reference = images[0].asPixelData();

                    assert.notEqual(images[1], undefined, "Original image");
                    assert.notEqual(images[0], undefined, "Reference image"); 

                    assert.notEqual(original, undefined, "Pixels of original image");
                    assert.notEqual(reference, undefined, "Pixels of reference image");

                    assert.equal(original.width, reference.width, "Image width");
                    assert.equal(original.height, reference.height, "Image height");
                    assert.equal(original.data.length, reference.data.length, "Length of data elements");

                    result = Utilities.compareImages(original, reference, [1]);
                    console.log(result);
                    assert.equal(result.isIdentical, true, "Correct pixel values (" + result.comment + ")");
                    done();
                });
            }

            QUnit.test("PyrDown 1 layer", function(assert) { return test_pyrdown(assert, 1); });
            QUnit.test("PyrDown 2 layer", function(assert) { return test_pyrdown(assert, 2); });
            QUnit.test("PyrDown 3 layer", function(assert) { return test_pyrdown(assert, 3); });
            //QUnit.test("PyrDown 4 layer", function(assert) { return test_pyrdown(assert, 4); });
        }
    }
});