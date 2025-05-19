 // Load the http server and the model
 const httpServer = require('./servers/http');
 const resources = require('./resources/model');

 // Require all the sensor plugins we need
 const ledsPlugin = require('./plugins/ledsPlugin');
 const pirPlugin = require('./plugins/pirPlugin');
 const tempPlugin = require('./plugins/tempPlugin');
 const lightPlugin = require('./plugins/lightPlugin');

 // Start them with a parameter object. Here we start them on a
 // laptop so we activate the simulation function
 ledsPlugin.start({'simulate': true, 'frequency': 2000});
 pirPlugin.start({'simulate': true, 'frequency': 1000});
 tempPlugin.start({'simulate': true, 'frequency': 10000});
 lightPlugin.start({'simulate': true, 'frequency': 10000});

 // Start the HTTP server by invoking listen() on the Express application
 const server = httpServer.listen(resources.iot.port, function () {
  // Once the server is started the callback is invoked
  console.info('Your WoT Pi is up and running on port %s', resources.iot.port);
 });
