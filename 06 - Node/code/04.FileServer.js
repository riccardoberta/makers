const http = require("http");
const fs = require("fs");
const mime = require("mime");

// An object called methods to store the functions that handle
// the various HTTP methods
const methods = Object.create(null);

http.createServer(function(request, response) {

  // A function to finish the request. It takes an HTTP
  // status code, a body, and optionally a content type as arguments.
  // If the value passed as the body is a readable stream,
  // it will have a pipe method, which is used to forward a readable
  // stream to a writable stream. If not, it is assumed to be either
  // null (no body) or a string and is passed directly
  // to the response’s end method.
  function respond(code, body, type){
	if (!type) type = "text/plain"; 
	response.writeHead(code, {"Content-Type":type});
    if (body && body.pipe) body.pipe(response);
    else response.end(body);
  }

  // The respond function is passed to the functions that
  // handle the various methods and acts as a callback to finish
  // the request.
  if(request.method in methods) methods[request.method](urlToPath(request.url), respond, request);
  // Returns 405 error responses, which is the
  // code used to indicate that a given method isn’t handled
  // by the server
  else respond(405, "Method " + request.method + " not allowed.");

}).listen(8000);

// A function to get a path from the URL in the request,
// it uses Node’s built-in "url" module to parse the URL.
// It takes its pathname, which will be something like /file.txt,
// decodes that to get rid of the %20-style escape codes,
// and prefixes a single dot to produce a path relative
// to the current directory.
function urlToPath(url) {
  var path = require("url").parse(url).pathname;
  return "." + decodeURIComponent(path);
};

// A method to manage GET request. It returns a list of files
// when reading a directory, and the file’s content when reading
// a regular file.
// One tricky question is what kind of Content-Type header we
// should add? Since these files could be anything, our
// server can’t simply return the same type for all of them.
// NPM can  help with that:  the "mime" package knows the correct
// type for a huge amount of file extensions.
methods.GET = function(path, respond){
  	// Because it has to touch the disk, and thus might take a while, fs.stat
  	// is asynchronous. When the file does not exist, fs.stat will pass
  	// an error code property of "ENOENT" to its callback.
	fs.stat(path, function(error, stats){
		// Codes starting with 4 (such as 404) refers to bad requests
		if( error && error.code=="ENOENT") respond(404, "File not found");
		// Codes starting with 5 (such as 500) refers to a server problem
      	else if (error) respond(500, error.toString());
    	else if (stats.isDirectory())
      		fs.readdir(path, function(error, files){
        		if (error) respond(500, error.toString())
        		else respond(200, files.join("\n"));
      		});
    	else
			console.log(path);
      		respond(200, fs.createReadStream(path), mime.getType(path));
	});
};

methods.POST = function(path, respond, request){
  	fs.stat(path, function(error, stats) {
    	if( error && error.code=="ENOENT") {
      		const outStream = fs.createWriteStream(path);
      		outStream.on("error", function(error) { respond(500, error.toString()); });
      		outStream.on("finish", function() { respond(204); });
      		// We use pipe to move data from a readable stream to a writable one,
      		// in this case from the request to the file
      		request.pipe(outStream);
    	}
		// Codes starting with 5 (such as 500) refers to a server problem
        else if (error)	respond(500, error.toString());
    	else  respond(400, "The file already exists");
  	});
};

// The code to handle a delete requests
methods.DELETE = function(path, respond) {
  	fs.stat(path, function(error, stats) {
		// You may be wondering why trying to delete a nonexistent file
      	// returns a 204 ("no content") status, rather than an error.
      	// When the file that is being deleted is not there, you could say
      	// that the request’s objective is already fulfilled.
      	// The HTTP standard encourages people to make requests idempotent.
		if (error && error.code == "ENOENT") respond(204);
    	else if (error) respond(500, error.toString());
    	else if (stats.isDirectory()) fs.rmdir(path, respondErrorOrNothing(respond));
    	else fs.unlink(path, respondErrorOrNothing(respond));
  	});
};

function respondErrorOrNothing(respond) {
	return function(error) {
		if (error) respond(500, error.toString());
      	else respond(204);
  	};
}

// The code for the PUT request
methods.PUT = function(path, respond, request) {
	const outStream = fs.createWriteStream(path);
  	outStream.on("error", function(error) { respond(500, error.toString());	});
  	outStream.on("finish", function() { respond(204); });
  	// We use pipe to move data from a readable stream to a writable one,
  	// in this case from the request to the file
  	request.pipe(outStream);
};

