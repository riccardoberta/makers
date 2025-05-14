// Go to http://eloquentjavascript.net/ before try the code

// Create a new XMLHttpRequest object
let req = new XMLHttpRequest();

// Make a GET request to the server
req.open("GET", "example/data.txt", false);
req.send(null);

// Display the response from the server
console.log(req.status, req.statusText);
console.log(req.getResponseHeader("content-type"));
console.log(req.responseText);