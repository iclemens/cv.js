define(['QUnit', 'tests/Utilities', '@iclemens/cv', '@iclemens/rxcv', 'rxjs'], function(QUnit, Utilities, CV, RxCV, Rx)
{
    return { 
        "run": function() {
            
            QUnit.test("Lukas-Kanade", function(assert) {
                var done = assert.async();

                var previousImage = new RxCV.LoadImage();
                previousImage.url = "reference/lk/previous.png";
                previousImage = previousImage.Generate();

                var currentImage = new RxCV.LoadImage();
                currentImage.url = "reference/lk/current.png";
                currentImage = currentImage.Generate();

                var referenceFile = 'reference/lk/reference.10.points.json';
                var reference = Rx.Observable.create(function(observer) {
                    $.get(referenceFile).then(function(result) {
                        observer.onNext(result);
                        observer.onCompleted();
                    }, function(ajax, error) {
                        observer.onError("Error loading reference: " + error);
                    });
                });                

                var gsP = new RxCV.Grayscale();
                var gsC = new RxCV.Grayscale();
                var lk = new CV.LK(4);
                
                previousImage = gsP.Process(previousImage);
                currentImage = gsC.Process(currentImage);

                Rx.Observable.combineLatest([previousImage, currentImage, reference]).subscribe(function(args) {
                    var prevImg = args[0];
                    var curImg = args[1];
                    var ref = args[2];
                    
                    var prevPts = [];
                    for(var i = 0; i < ref.length; i++) {
                        prevPts.push(ref[i].previous);
                    }                    
                   
                    var winSize = 31;
                    var curPts = lk.calcOpticalFlowPyrLK([prevImg], [curImg], prevPts, winSize, 4);

                    console.log(prevPts[0], ref[0].current, curPts.nextPts[0]);
                    
                    assert.equal(ref[0].current.x, curPts.nextPts[0].x, "X coordinate of first point");
                    assert.equal(ref[0].current.y, curPts.nextPts[0].y, "Y coordinate of first point");
                    
                    //var original = images[1].asPixelData();
                    //var reference = images[0].asPixelData();

                    done();
                });
            });
        } 
    }
});