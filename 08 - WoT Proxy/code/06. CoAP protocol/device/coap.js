// Require the Node.js CoAP module you installed
const coap = require('coap');
const port = 5683;

coap.createServer(function (req, res) {
  console.info('CoAP device got a request for %s', req.url);
  
  // We only serve JSON, so we reply with a 4.06 (= HTTP 406: Not acceptable)
  if (req.headers['Accept'] != 'application/json') {
    res.code = '4.06';
    return res.end();
  }
  
  // Handle the different resources requested
  switch (req.url) {
    // This is a simulated CO2 resource; generate a random value for it and respond
    case "/co2":
      respond(res, {'co2': Math.floor(Math.random() * 1000)});
      break;
    default:
      respond(res);
  }
}).listen(port, function () {
  // Start the CoAP server on port 5683 (CoAP’s default port)
  console.log("CoAP server started on port %s", port)
});

//# Send the JSON content back or reply with a 4.04 (= HTTP 404: Not found)
function respond(res, content) {
  if (content) {
    res.setOption('Content-Format', 'application/json');
    res.code = '2.05';
    res.end(JSON.stringify(content));
  } else {
    res.code = '4.04';
    res.end();
  }
};





