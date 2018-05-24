define(['QUnit', 'tests/Utilities', 'rxjs', '@iclemens/cv', '@iclemens/rxcv'], function(QUnit, Utilities, Rx, CV, RxCV)
{
    return {
        "run": function() {
            function test_fast_private(assert, S, mask, T, nonmax, method) {
                var done = assert.async();
                
                // Build filename
                var suffix = ".json";
                
                if(nonmax)
                    suffix = ".nms.json";
                
                var referenceFile = "reference/" +  method + "/" + "lab." + method + "_" + S + "_" + mask + "_" + T + suffix;

                // Load input image
                const originalImage = new RxCV.LoadImage();
                originalImage.url = "reference/lab.grayscale.png";
                const originalImage$ = originalImage.Generate();

                var canvasSink = new RxCV.CanvasSink(document.getElementById('output'));

                let fast$;

                if(method == "fast") {
                    fast$ = originalImage$.pipe(RxCV.fast(mask, T, S, nonmax, false));
                } else if(method == "agast") {
                    fast$ = originalImage$.pipe(RxCV.agast(mask, T, S, nonmax, false));
                }
                
                const reference$ = Rx.Observable.create(function(observer) {
                    $.get(referenceFile).then(function(result) {
                        observer.next(result);
                        observer.complete();
                    }, function(ajax, error) {
                        observer.error("Error loading reference data: " + error);
                    });
                });
                
                Rx.combineLatest([fast$, reference$]).subscribe(function(input) {
                    var features = input[0];
                    var reference = input[1];

                    //if(mask == 8) console.log(S, T, features);

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
                        if(reference[i].x == features[i].x && 
                        reference[i].y == features[i].y &&
                        (reference[i].response == 0 || reference[i].response == features[i].score))
                            continue;
                            
                        console.log(reference[i], features[i]);
                        incorrect++;
                    }
                    
                    assert.equal(incorrect, 0, 'Correct features detected (' + incorrect + ')');
                    done();
                });
            }


            var thresholds = [50, 30, 20, 10];
            for(var i = 0; i < thresholds.length; i++) {
                var threshold = thresholds[i];

                (function(threshold) {
                    //QUnit.module("{F,AG}AST 16-9");
                    QUnit.test("FAST 16-9 T" + threshold, function(assert) {
                        // console.log("Passing", threshold);
                        test_fast_private(assert, 9, 16, threshold, false, "fast"); 
                    });
                    
                    QUnit.test("AGAST 16-9 T" + threshold, function(assert) {
                        test_fast_private(assert, 9, 16, threshold, false, "agast"); 
                    });
                    
                    QUnit.test("FAST 16-9 T" + threshold + " NMS", function(assert) { 
                        test_fast_private(assert, 9, 16, threshold, true, "fast"); 
                    });
                    
                    QUnit.test("AGAST 16-9 T" + threshold + " NMS", function(assert) {
                        test_fast_private(assert, 9, 16, threshold, true, "agast"); 
                    });
                        
                    //QUnit.module("{F,AG}AST 8-5");
                    /*QUnit.test("FAST 8-5 T" + threshold, function(assert) {
                        console.log("Passing", threshold);
                        test_fast_private(assert, 5, 8, threshold, false, "fast"); 
                    });*/
                    
                    QUnit.test("AGAST 8-5 T" + threshold, function(assert) {
                        test_fast_private(assert, 5, 8, threshold, false, "agast"); 
                    });
                    
                    /*QUnit.test("FAST 8-5 T" + threshold + " NMS", function(assert) { 
                        test_fast_private(assert, 5, 8, threshold, true, "fast"); 
                    });*/
                    
                    QUnit.test("AGAST 8-5 T" + threshold + " NMS", function(assert) {
                        test_fast_private(assert, 5, 8, threshold, true, "agast"); 
                    });        
                }(threshold));    
            }
        }
    }
});