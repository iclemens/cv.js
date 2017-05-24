var fs = require('fs');
var sax = require('sax');

/**
 * Extension to the SAX parser that keeps track
 * of the path to the current node.
 */
function Parser()
{
    this.pathArray = [];
    
    this.onopentag = function(path, node) { }
    this.onclosetag = function(path) { }
    this.ontext = function(path, text) { }
    
    this.parse = function(xmlSource) {
        this.pathArray = [];
        this.path = '';
        
        var parser = sax.parser(true);
        
        parser.onopentag = function(node) {
            this.pathArray.push(node.name);
            this.path = this.pathArray.join(".");
            
            this.onopentag(this.path, node);
        }.bind(this);
        
        parser.ontext = function(text) {
            this.ontext(this.path, text);
        }.bind(this);
        
        parser.onclosetag = function() {
            this.onclosetag(this.path);
            this.pathArray.pop();
            this.path = this.pathArray.join(".");
        }.bind(this);
        
        parser.write(xmlSource).close();
    }
}


/**
 * Class that collects features (composed of rectangles).
 */
function FeatureCollector()
{
    this.current = [];
    this.features = {};
    this.featureCount = 0;
    
    this.openFeature = function() {
        this.current = [];
    }
    
    this.closeFeature = function() {
        this.features[this.featureCount++] = this.current;
        this.current = [];
    }
    
    this.addRect = function(rectText) {
        var r = rectText
            .split(/[ \t\n]+/)
            .filter(function(x) { return x.length > 0 })
            .map(function(x) { return parseFloat(x); });
        this.current.push(r);
    }
}


/**
 * Class that collects information about the stages
 * and composes it into an object.
 */
function StageCollector()
{
    this.stages = [];
    this.stage = {};
    
    this.internalNode = [];
    this.leafValues = [];
    
    this.openStage = function() {
        this.stage = { classifiers: [] };
        this.internalNode = [];
        this.leafValues = [];
    }
    
    this.closeStage = function() {
        this.stages.push(this.stage);
        this.stage = {};
    }
    
    this.setThreshold = function(text) {
        this.stage.threshold = parseFloat(text);
    }
    
    this.addClassifier = function()
    {
        var classifier = {};
        classifier.left_val = this.leafValues[0];
        classifier.right_val = this.leafValues[1];
        classifier.feature = this.internalNode[2];
        classifier.threshold = this.internalNode[3];

        this.stage.classifiers.push(classifier);
        
        this.internalNode = [];
        this.leafValues = [];
    }
    
    this.setInternalNode = function(text) {
        var r = text
            .split(/[ \t\n]+/)
            .filter(function(x) { return x.length > 0; })
            .map(function(x) { return parseFloat(x); });
        this.internalNode = r;
    }
    
    this.setLeafValues = function(text) {
        var r = text
            .split(/[ \t\n]+/)
            .filter(function(x) { return x.length > 0; })
            .map(function(x) { return parseFloat(x); });
        this.leafValues = r;
    }
}


function LoadCascadeFromNewXML(source)
{
    var parser = new Parser();
    
    var features = new FeatureCollector();
    var stages = new StageCollector();
    var output = {};
    
    parser.onopentag = function(path, node) {
        if(path == 'opencv_storage.cascade.features._.rects')
            features.openFeature();
        if(path == 'opencv_storage.cascade.stages._')
            stages.openStage();
            
    }

    parser.onclosetag = function(path) {
        if(path == 'opencv_storage.cascade.features._.rects')
            features.closeFeature();
        if(path == 'opencv_storage.cascade.stages._')
            stages.closeStage();
        if(path == 'opencv_storage.cascade.stages._.weakClassifiers._')
            stages.addClassifier();
    }
    
    parser.ontext = function(path, text) {
        if(path == 'opencv_storage.cascade.features._.rects._')
            features.addRect(text);
        if(path == 'opencv_storage.cascade.stages._.stageThreshold')
            stages.setThreshold(text);
            
        if(path == 'opencv_storage.cascade.stages._.weakClassifiers._.internalNodes')
            stages.setInternalNode(text);            
        if(path == 'opencv_storage.cascade.stages._.weakClassifiers._.leafValues')
            stages.setLeafValues(text);
        
        if(path == 'opencv_storage.cascade.height')
            output.height = parseFloat(text);
        if(path == 'opencv_storage.cascade.width')
            output.width = parseFloat(text);
    }
    
    parser.parse(source);
    output.stages = stages.stages;
    output.features = features.features;
    return output;
}


/**
 * Converts the Cascade to TypeScript
 */
function GenerateTSCascade(name, cascade)
{
    var json = "import {CascadeInterface} from '../Cascade'\n\nexport var " + name + ": CascadeInterface = {\n";
    json += "\tsize: [" + cascade.width + ", " + cascade.height + "],\n";
    json += "\tstages: [\n";
    
    for(var i = 0; i < cascade.stages.length; i++) {
        var rects = "";
        var classifiers = cascade.stages[i].classifiers;

        // Build list of thresholds and left/right values        
        var thresholdsN2D = classifiers
            .map(function(x) { return [ x.threshold, x.left_val, x.right_val ]; });
        var thresholdsN = [].concat.apply([], thresholdsN2D);
        thresholdsN.push(cascade.stages[i].threshold);
        var thresholds = thresholdsN.join(", ");
        
        // Build list of rectangles
        var featuresN2D = classifiers
            .map(function(x) { 
                var feature = cascade.features[ x.feature ]; 
                if(feature.length == 2)
                    feature.push([0, 0, 0, 0, 0]);
                return feature;
            });
        var featuresN = [].concat.apply([], 
                        [].concat.apply([], featuresN2D));
        var features = featuresN.join(", ");
        
        json += "\t\t{\n";
        json += "\t\t\tthresholds: new Float64Array([" + thresholds + "]),\n";
        json += "\t\t\trects: new Int32Array([" + features + "]),\n";
        json += "\t\t},\n";
    }
    
    json += "\t]\n";
    json += "}\n";
    
    return json;
}


function GenerateShaderCascade(name, cascade)
{
    var shader = "";

    shader += "/**\n * Haar Cascade\n * Usage: " + name + "();\n */\n\n";

    shader += "precision highp float;\n\n";

    shader += "varying vec2 v_texcoord;\n" +
              "uniform sampler2D ii;\n" +
              "uniform sampler2D ii2;\n" +
              "uniform float invArea;\n" +
              "uniform float iiMax;\n" +
              "uniform float ii2Max;\n" +
              "uniform float scale;\n" +
              "uniform vec2 pixelSizeIn;\n\n";
    
    // The sample() function unpacks the pixel value from the RGB
    // components. To obtain the actual result, multiply with
    // maxII or maxII2.
    var textures = ['ii', 'ii2'];
    for(i in textures) {
        shader += "float sample_" + textures[i] + "(vec2 coord)\n{\n" +
                    "\tvec4 value = texture2D(" + textures[i] + ", coord);\n" +
                    "\tfloat r = value.r * 255.0;\n" +
                    "\tfloat g = value.g * 255.0;\n" +
                    "\tfloat b = value.b * 255.0;\n" +
                    "\treturn (b * 65536.0 + g * 256.0 + r) / 16777215.0 * " + textures[i] + "Max;\n" +
                    "}\n\n";
    
        // Compute the sum of pixels in a rectangle.
        shader += "float rect_sum_" + textures[i] + "(float x, float y, float w, float h, float weight)\n";
        shader += "{\n";
        shader += "\tvec2 topLeft = v_texcoord + vec2(x * scale * pixelSizeIn.x, y * scale * pixelSizeIn.y);\n" +
                    "\tvec2 topRight = topLeft + vec2(w * scale * pixelSizeIn.x, 0.0);\n" +
                    "\tvec2 bottomLeft = topLeft + vec2(0.0, h * scale * pixelSizeIn.y);\n" +
                    "\tvec2 bottomRight = bottomLeft + vec2(w * scale * pixelSizeIn.x, 0.0);\n\n";
        shader += "\treturn weight * (sample_" + textures[i] + "(bottomRight) + \n" +
                    "\t\tsample_" + textures[i] + "(topLeft) - sample_" + textures[i] + 
                    "(topRight) - sample_" + textures[i] + "(bottomLeft));\n"          
        shader += "}\n\n";
    }
    
    // Create function named CascadeName_stage#()
    // for every stage. It will return either 0 or 1
    // depending on whether the stage passes (1.0) or 
    // not (0.0).
    var numStages = cascade.stages.length;
    numStages = 15;
    
    for(var i = 0; i < numStages; i++) {
        var stage = cascade.stages[i];
        
        shader += "int " + name + "_stage" + i + "(float factor)\n" +
                  "{\n" +
                  "\tfloat sum;\n" +
                  "\tfloat stage_sum;\n";
        
        for(var j = 0; j < stage.classifiers.length; j++) {
            var classifier = stage.classifiers[j];
            var feature = cascade.features[classifier.feature];
            
            shader += "\n\tsum = 0.0;\n";
            
            for(var k = 0; k < feature.length; k++) {
                shader += "\tsum += rect_sum_ii(" + 
                    feature[k][0] + ".0, " + 
                    feature[k][1] + ".0, " +
                    feature[k][2] + ".0, " + 
                    feature[k][3] + ".0, " +
                    feature[k][4] + ".0);\n";
            }
            
            shader += "\tif(sum < " + classifier.threshold + " * factor)\n";
            shader += "\t\tstage_sum += " + classifier.left_val + ";\n";
            shader += "\telse\n";            
            shader += "\t\tstage_sum += " + classifier.right_val + ";\n";
        }
        
        shader += "\n\n\tif(stage_sum > " + stage.threshold + ")\n" +
                  "\t\treturn 1;\n" +
                  "\telse\n" +
                  "\t\treturn 0;\n";
        
        shader += "}\n\n";
    }
    
    
    // Create a function called CascadeName() that combines
    // the output of the different shaders.
    shader += "vec4 " + name + "()\n";
    shader += "{\n";
    
    // First we need to compute the "factor" which is the
    // standard deviation / inverse area.
    shader += "\tfloat invArea = 1.0 / (scale * " + cascade.width + ".0 * scale * " + cascade.height + ".0);\n";
    shader += "\tfloat mean = rect_sum_ii(v_texcoord.x, v_texcoord.y, " + cascade.width + ".0, " + cascade.height + ".0, invArea);\n";
    shader += "\tfloat variance = rect_sum_ii2(v_texcoord.x, v_texcoord.y, " + cascade.width + ".0, " + cascade.height + ".0, invArea) - (mean * mean);\n";
    shader += "\tfloat std = sqrt(variance);\n";    
    
    for(var i = 0; i < numStages; i++) {
        shader += "\tif(" + name + "_stage" + i + "(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);\n";
    }    
    shader += "\treturn vec4(1.0, 1.0, 1.0, 1.0);\n";
    shader += "}\n\n";
    
    shader += "void main()\n{\n" + 
              "\tgl_FragColor = " + name + "();\n" +
              "}\n"
    
    return shader;
}


exports.compileSingleCascade = function(inputFilename, outputFilename, baseName, type)
{
    var data = fs.readFileSync(inputFilename, 'utf-8');

    var cascade = LoadCascadeFromNewXML(data);
    
    if(type == 'shader') {
        var shader = GenerateShaderCascade(baseName, cascade);
        fs.writeFileSync(outputFilename, shader);
    } else if(type == 'typescript') {
        var typescript = GenerateTSCascade(baseName, cascade);
        fs.writeFileSync(outputFilename, typescript);
    } 

}

exports.compileAllCascades = function()
{
    var cascadeDirectory = "src/data/cascade";
    var shaderDirectory = "src/data/shaders/generated";
    var typescriptDirectory = "src/objdetect/cascades";

    var files = fs.readdirSync(cascadeDirectory);
    var main = "";

    for(let i = 0; i < files.length; i++)
    {
        if(!files[i].endsWith(".xml")) continue;

        let baseName = files[i].slice(0, -4);
        let cascadeFilename = cascadeDirectory + "/" + files[i];
        let shaderFilename = shaderDirectory + "/" + baseName + ".frag.c";
        let typescriptFilename = typescriptDirectory + "/" + baseName + ".ts";

        console.log("Compiling", baseName);
        exports.compileSingleCascade(cascadeFilename, shaderFilename, baseName, "shader");
        exports.compileSingleCascade(cascadeFilename, typescriptFilename, baseName, "typescript");
        
        main += "export * from './" + baseName + "'\n";
    }
    
    fs.writeFileSync(typescriptDirectory + '/main.ts', main);
}
