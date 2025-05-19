// Make sure we are running node 7.6+
const [major, minor] = process.versions.node.split('.').map(parseFloat);
if (major < 7 || (major === 7 && minor <= 5)) {
  console.log('Older version of node, upload to 7.6 or greater\n');
  process.exit();
}

// Import environmental variables
if(process.argv[2] === undefined) {
  require('dotenv').config({ path: 'variables.dev.env' });
  console.log("DEV Environment");
}
else if(process.argv[2] === "-prod") {
  require('dotenv').config({ path: 'variables.prod.env' });
  console.log("PROD Environment");
}
 
// Load the databse, the http server, the websocekt server and the model
const db = require('./database');

const httpServer = require('./servers/http');
const resources = require('./resources/model');
const wsServer = require('./servers/websockets');

// Require all the sensor plugins we need
const ledsPlugin = require('./plugins/ledsPlugin');
const pirPlugin = require('./plugins/pirPlugin');
const tempPlugin = require('./plugins/tempPlugin');
const lightPlugin = require('./plugins/lightPlugin');

// Start them with a parameter object. Here we start them on a
// laptop so we activate the simulation function
ledsPlugin.start({'simulate': true, 'frequency': 1000});
pirPlugin.start({'simulate': true, 'frequency': 1000});
tempPlugin.start({'simulate': true, 'frequency': 1000});
lightPlugin.start({'simulate': true, 'frequency': 1000});
 
const server = httpServer.listen(resources.iot.port, function () {
   console.info('Your WoT Pi is up and running on port %s', resources.iot.port);
});
 
// Websockets server
wsServer.listen(server);
 