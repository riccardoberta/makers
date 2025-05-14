var http = require('http');

var request = http.request({
  // telling Node what server to talk to
  hostname: "eloquentjavascript.net",
  //what path to request from that server
  path: "/img/cover.jpg",
  // which method to use
  method: "GET",
  headers: {Accept: "text/html"}
  },
  // the function that should be called when a response comes in
  function(response) {
      console.log("Server responded with status code: ", response.statusCode);
  });

request.end();