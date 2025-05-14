// Include the HHTP library into the program
// the functionality of the library are assigned to the “http” object
var http = require('http');

// Unlike other languages (PHP) that run inside a server (e.g. Apache)
// Node itself acts as a web server.
// CreateServer takes a callback function as an argument.
// This callback function is executed each time the server receives a
// new request.
// The callback function takes two arguments, request and response.
// The request object contains information regarding the client’s request,
// such as the URL, HTTP headers, and much more.
// Similarly, the response object is used to return data back to the client.
// The server is initialized and listen on port 8124
http.createServer(function (request, response) {
    console.log("Esecuzione in seguito a evento");
    response.writeHead(200, {'Content-Type': 'text/plain'});
    response.end('Hello World\n');
}).listen(8124, "127.0.0.1");

console.log('Server running at http://127.0.0.1:8124/');
