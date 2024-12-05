// Include the net library, that contains all the TPC stuff
const net = require('net');

// Create a TCP server
const chatServer = net.createServer();

// A list of client connections
const clientList = [];

// Add a event listener using the on method whenever a "connection event happens, the listener
// will be called. The event provides a reference to the TPC socket for the new client
chatServer.on('connection', function(client) {
	// decorate the client with an additional property, the name,
    // using the existing properties "remoteAddress" and "remotePort"
    client.name = client.remoteAddress + ':' + client.remotePort;

    // with "write" we can send messages to the new client
    client.write('Hi ' + client.name + '!\n');

    // add the new client to the list
    clientList.push(client);

    // another event listener, it's in the scope of the connection callback method, we need to access the client.
    // The event is called "data", it is fired each time client sends some data to the server.
    client.on('data', function(data) { broadcast(data, client) });
});

// A method to send messages to all client, filtering the sender
function broadcast(message, client) {
	for(let i=0; i<clientList.length; i+=1) {
    	if(client !== clientList[i]) { clientList[i].write(client.name + " says " + message); }
  	}
}

// The port on which Node is listen to
chatServer.listen(80)
