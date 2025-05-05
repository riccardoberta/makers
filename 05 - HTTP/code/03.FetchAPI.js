// Go to http://eloquentjavascript.net/ before try the code

// Create an async function to use await inside it
async function fetchData() {
    // Initiating a fetch request to get the content of "example/data.txt"
    let response = await fetch("example/data.txt");

    // Logging the HTTP status code, status message and content type of the response
    console.log(response.status, response.statusText);
    console.log(response.headers.get("content-type"));

    // Reading the response body as text and logging it to the console
    let text = await response.text();
    console.log(text);
}

// Call the function
fetchData();