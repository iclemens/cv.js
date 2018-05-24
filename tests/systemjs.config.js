(function(global) {


  var map = {
    'tests': 'src',

    'rxjs':  'npm:rxjs',
    'QUnit': 'npm:qunitjs',

    'jquery':                     'node_modules/jquery/dist',

    '@iclemens/cv':             'node_modules/@iclemens/cv',
    '@iclemens/rxcv':           'node_modules/@iclemens/rxcv'
  };


  var packages = {
    'QUnit': { main: 'qunit/qunit.js' },
    
    '@iclemens/cv':   { main: 'index.js', defaultExtension: 'js' },
    '@iclemens/rxcv': { main: 'index.js', defaultExtension: 'js' },

    'jquery': { main: 'jquery.min.js' },

    'tests': { defaultExtension: 'js' },
    'rxjs':  { main: 'index.js', defaultExtension: 'js' }
  };


  var config = {
    paths: {
      'npm:': 'node_modules/'
    },
    map: map,
    packages: packages
  };


  System.config(config);

})(this);
