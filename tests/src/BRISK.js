define(['QUnit', 'tests/Utilities', 'rxjs', '@iclemens/cv', '@iclemens/rxcv'], function(QUnit, Utilities, Rx, CV, RxCV)
{    
    function test_brisk_private(assert, octave) { 
        var done = assert.async();
        
        var referenceFile = "reference/lab.brisk.keypoints.o" + octave + ".json";
        
        var originalImage = new RxCV.LoadImage();
        originalImage.url = "reference/lab.grayscale.png";
        originalImage = originalImage.Generate();

        var canvasSink = new RxCV.CanvasSink();
        canvasSink.element = document.getElementById('output');

        var brisk = new RxCV.BRISK();
        brisk.T = 50;
        brisk.octaveCount = octave;   
        brisk = brisk.Process(originalImage);
        
        var reference = Rx.Observable.create(function(observer) {
            $.get(referenceFile).then(function(result) {
                observer.next(result);
                observer.complete();
            }, function(ajax, error) {
                observer.error("Error loading reference: " + error);
            });
        });
        
        Rx.Observable.combineLatest([brisk, reference]).subscribe(function(input) {
            console.log("Got: ", input);
            var features = input[0];
            var reference = input[1];

            // Compare results
            assert.equal(features.length, reference.length, 'Number of detected features is correct (' + features.length + ')');
            if(features.length != reference.length) {
                console.log("Difference in length:", features.length, "found while expecting", reference.length);
            }
            
            var N = features.length;
            if(features.length > reference.length) {
                N = reference.length;
            }
            
            var incorrect = 0;
            for(var i = 0; i < N; i++) {
                var dx = Math.abs(reference[i].x - features[i].x);
                var dy = Math.abs(reference[i].y - features[i].y);
                var ds = Math.abs(reference[i].response - features[i].score);
                
                if(dx < 0.01 && dy < 0.01 && ds < 0.01) continue;            
                
                console.log('X', reference[i].x, 'Y', reference[i].y, 'R', reference[i].response, 'F', features[i]);
                incorrect++;
            }
            
            assert.equal(incorrect, 0, 'Correct features detected (' + (N - incorrect) + " correct and " +  incorrect + ' incorrect)');
            done();
        });     
    }

    return {
        run: function() {
            QUnit.test("BRISK Octave 0", function(assert) { test_brisk_private(assert, 0); });
            QUnit.test("BRISK Octave 1", function(assert) { test_brisk_private(assert, 1); });
            QUnit.test("BRISK Octave 5", function(assert) { test_brisk_private(assert, 5); });
        }
    };
});