 // Load the http server, the websocekt server and the model
 const httpServer = require('./servers/http');
 const resources = require('./resources/model');
 const wsServer = require('./servers/websockets');

 // Require all the sensor plugins we need
 const ledsPlugin = require('./plugins/ledsPlugin');
 const pirPlugin = require('./plugins/pirPlugin');
 const tempPlugin = require('./plugins/tempPlugin');
 const lightPlugin = require('./plugins/lightPlugin');
 const coapPlugin = require('./plugins/coapPlugin');

 // Start them with a parameter object. Here we start them on a
 // laptop so we activate the simulation function
 ledsPlugin.start({'simulate': true, 'frequency': 1000});
 pirPlugin.start({'simulate': true, 'frequency': 1000});
 tempPlugin.start({'simulate': true, 'frequency': 1000});
 lightPlugin.start({'simulate': true, 'frequency': 1000});
 coapPlugin.start({'simulate': false, 'frequency': 1000});

 const server = httpServer.listen(resources.iot.port, function () {
  console.info('Your WoT Pi is up and running on port %s', resources.iot.port);
 });
 
 // Websockets server
 wsServer.listen(server);
 
