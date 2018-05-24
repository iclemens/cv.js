(function(global) {

  var map = {
    'app': 'dist',

    'rxjs':   'npm:rxjs',
    'jquery': 'node_modules/jquery/dist',

    '@iclemens/cv':   'node_modules/@iclemens/cv',
    '@iclemens/rxcv': 'node_modules/@iclemens/rxcv',
  };

  var packages = {
    '@iclemens/cv':   { main: 'index.js', defaultExtension: 'js' },
    '@iclemens/rxcv': { main: 'index.js', defaultExtension: 'js' },

    'jquery': { main: 'jquery.min.js' },

    'app':  { defaultExtension: 'js' },
    'rxjs': { defaultExtension: 'js', 'main': 'index.js' },
    'rxjs/operators': { defaultExtension: 'js', 'main': 'index.js' }
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
