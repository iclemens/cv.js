define(['QUnit'], function(QUnit)
{
    return {
        /**
         * Compares pixel-data for two images
         */
        
        "compareImages":    
            function compareImages(image1, image2, layers)
            {                
                if(layers === undefined) layers = [0, 1, 2, 3];
                
                if(image1.height != image2.height ||
                image1.width != image2.width) {
                    return { isIdentical: false, comment: "Dimensions do not match" };
                }
                
                var scenarios = ["image is upright", "y axis is flipped", "both axes are flipped", "x axis is flipped"];
                var perfect = [0, 0, 0, 0];
                var rounding = [0, 0, 0, 0];
                var d = 4;
                var l = layers.length;
                
                var maxScore = image1.width * image1.height * l;
                
                var offsets = [0, 0, 0, 0];
                                
                for(var y = 0; y < image1.height; y++) {
                    for(var x = 0; x < image1.width; x++) {
                        var yf = image1.height - y - 1;
                        var xf = image1.width - x - 1;
                        
                        // Normal
                        offsets[0] = d * (y * image1.width + x);
                
                        // Flipped V, HV, H
                        offsets[1] = d * (yf * image1.width + x);
                        offsets[2] = d * (yf * image1.width + xf);
                        offsets[3] = d * (y * image1.width + xf);
                        
                        for(var c = 0; c < l; c++) {
                            var loffset = layers[c];
                            for(var s = 0; s < 4; s++) {
                                var delta = Math.abs(image1.data[offsets[0] + loffset] - image2.data[offsets[s] + loffset]);
                                
                                if(delta == 0)
                                    perfect[s]++;
                                else if(delta == 1)
                                    rounding[s]++;
                            }
                        }
                    }
                }

                // Find maximum
                var maxI = 0;
                var maxV = perfect[0];
                
                for(var s = 1; s < perfect.length; s++) {
                    if(perfect[s] > maxV) {
                        maxI = s;
                        maxV = perfect[s];
                    }
                }

                var isIdentical = perfect[0] + rounding[0] - maxScore == 0;
                isIdentical = false;
                if(!isIdentical) {
                    lines = 0;
                    for(var y = 0; y < image1.height; y++) {
                        for(var x = 0; x < image1.width; x++) {
                            for(var d = 0; d < l; d++) {
                                var dd = layers[d];
                                var offset = ((y * image1.width) + x) * 4 + dd;
                                
                                if(lines < 20 && Math.abs(image1.data[offset] - image2.data[offset]) > 0) {
                                    console.log('Coordinate:', y, x, d, 'Values:', image1.data[offset], image2.data[offset]);
                                    lines++;
                                }
                            }
                        }
                    }
                }

                // Return result
                return {
                    isIdentical: (perfect[0] + rounding[0] - maxScore > -10),   // Accepts some erroneous pixels :(
                    pctIdentical: (perfect[0] + rounding[0]) / maxScore * 100.0,        
                    
                    hasRoundingErrors: rounding[0] != 0,
                    pctRoundingErrors: 100.0 * (rounding[0]/maxScore),
                    cntRoundingErrors: rounding[0],
                    
                    comment: scenarios[maxI] + ", " + Math.floor(100*maxV/maxScore) + "% sure, " +
                             (maxScore - perfect[0]) + " incorrect, " + rounding[0] + " rounding errors"
                };
            }
    }
});
