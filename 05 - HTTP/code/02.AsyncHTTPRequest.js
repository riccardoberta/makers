// Go to http://eloquentjavascript.net/ before try the code

// Create a new XMLHttpRequest object
let req = new XMLHttpRequest();

// Define a callback function to handle the response
function transferComplete(evt) {
    console.log("The transfer is complete.");
}

// Make a GET request to the server, providing the callback function
req.open("GET", "example/data.txt", true);
req.addEventListener("load", transferComplete);
req.send(null);

//Log a message to the console
console.log("I'm here.");

