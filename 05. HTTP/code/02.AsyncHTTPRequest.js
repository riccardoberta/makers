// Go to http://eloquentjavascript.net/ before try the code

let req = new XMLHttpRequest();
req.open("GET", "example/data.txt", true);
req.addEventListener("load", transferComplete);
function transferComplete(evt) {
  console.log("The transfer is complete.");
}
req.send(null);
console.log("Sono qui.");


