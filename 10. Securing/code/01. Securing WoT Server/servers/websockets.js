const WebSocketServer = require('ws').Server;
const resources = require('./../resources/model');
const observer = require("node-observer");

exports.listen = function(server) {
  // Create a WebSockets server by passing it the Express server
  const wss = new WebSocketServer({server: server});
  console.info('WebSocket server started...');
  
  // Triggered after a protocol upgrade when the client connected
  wss.on('connection', function (ws, req) {
    let url = req.url;
    console.info(url);
    try {
      // Register an observer corresponding to the resource in the protocol upgrade URL
      observer.subscribe(this, selectResouce(url).name, function(who, data) {
        ws.send(JSON.stringify(selectResouce(url).value), function () {});
      });
    }
    // Use a try/catch to catch to intercept errors (e.g., malformed/unsupported URLs)
    catch (e) { console.log('Unable to observe %s resource!', url); console.log(e); };
  });
};

// This function takes a request URL and returns the corresponding resource
function selectResouce(url) {
  let parts = url.split('/');
  parts.shift();
  let result = resources;
  for (let i = 0; i < parts.length; i++) { result = result[parts[i]]; }
  return result;
}








