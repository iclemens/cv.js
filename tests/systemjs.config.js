(function(global) {


  var map = {
    'tests': 'src',

    'es6-promise':                'node_modules/es6-promise/dist/es6-promise.js',
    'rxjs':                       'npm:rxjs',
    'QUnit':                      'npm:qunitjs',
    'heatmap':                    'node_modules/heatmap.js/heatmap.js',

    'jquery':                     'node_modules/jquery/dist',

    '@iclemens/stompjs':        'node_modules/@iclemens/stompjs',
    '@iclemens/cv':             'node_modules/@iclemens/cv/dist',
    '@iclemens/rxcv':           'node_modules/@iclemens/rxcv/dist',
    '@iclemens/eyetracker':     'node_modules/@iclemens/eyetracker/dist',
    '@iclemens/api':            'node_modules/@iclemens/api/dist',
  };


  var packages = {
    'QUnit':                    { main: 'qunit/qunit.js' },
    
    '@iclemens/cv':             { main: 'CV.js', defaultExtension: 'js' },
    '@iclemens/rxcv':           { main: 'RxCV.js', defaultExtension: 'js' },
    '@iclemens/eyetracker':     { main: 'EyeTracker.js', defaultExtension: 'js' },
    '@iclemens/api':            { main: 'MindTrace.js', defaultExtension: 'js' },

    'jquery':                     { main: 'jquery.min.js' },

    'local-messaging-client':     { main: 'messaging.js', defaultExtension: 'js' },
    'tests':                        { defaultExtension: 'js' },
    'rxjs':                       { main: 'Rx.js', defaultExtension: 'js' }
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
