// Go to http://eloquentjavascript.net/ before try the code

let req = new XMLHttpRequest();
req.open("GET", "example/data.txt", false);
req.send(null);
console.log(req.status, req.statusText);
console.log(req.getResponseHeader("content-type"));
console.log(req.responseText);
