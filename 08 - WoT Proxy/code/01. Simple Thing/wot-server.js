 // Load the http server and the model
 const httpServer = require('./servers/http');
 const resources = require('./resources/model');

 // Start the HTTP server by invoking listen() on the Express application
 const server = httpServer.listen(resources.iot.port, function () {
  // Once the server is started the callback is invoked
  console.info('Your WoT API is up and running on port %s', resources.iot.port);
 });
