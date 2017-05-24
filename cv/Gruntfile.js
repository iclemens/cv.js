module.exports = function(grunt) {
  var jsesc = require('jsesc');
  
  grunt.initConfig({    
    shaders: {
      base: 'src/data',
      src: {
        files: { '../core/StoredFiles.ts': ['shaders/**/*.c'] }
      },
    },
    
    cascades: { }
  });
  
  grunt.loadNpmTasks("grunt-contrib-uglify");
  
  function generateStoredFile(filename) {
    var contents = grunt.file.read(filename);
    var string = jsesc(contents, { 'quotes': 'double', 'wrap': true });
    return string;
  }
  
  var cascadeModule = require('./src/scripts/cascade');
  grunt.registerTask('cascades', '', cascadeModule.compileAllCascades);
  
  grunt.registerTask("shaders", "", function() {
    var base = grunt.config('shaders.base');
    var files = grunt.config("shaders.src.files");
    
    var oldBase = process.cwd();
    grunt.file.setBase(base);
    
    var storedFiles = "export var storedFiles = {\n";
    
    for(var outputFile in files) {
      var inputFiles = grunt.file.expand(files[outputFile]);

      for(var i = 0; i < inputFiles.length; i++) {
        var filename = inputFiles[i];
        
        storedFiles += "\t" + jsesc(inputFiles[i], { 'quotes': 'double', 'wrap': true }) + ": " +
          generateStoredFile(inputFiles[i]) + ", \n\n";
      }
    }
    
    storedFiles += "};\n";

    grunt.file.write(outputFile, storedFiles);
    grunt.file.setBase(oldBase);
  });
  
  grunt.registerTask("default", ['cascades', 'shaders']);
};
