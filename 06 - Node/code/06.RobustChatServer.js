const net = require('net');
const chatServer = net.createServer();
const clientList = [];

chatServer.on('connection', function(client) {
    client.name = client.remoteAddress + ':' + client.remotePort
    client.write('Hi ' + client.name + '!\n');
    console.log(client.name + ' joined');
    clientList.push(client);
    client.on('data', function(data) { broadcast(data, client) });

    // Add a new callback for the "end" event: it is fired
    // when a client disconnect. Now when the next client uses the
    // broadcast call, the disconncted client no longer be in the list
    client.on('end', function() {
        console.log(client.name + ' quit');
        clientList.splice(clientList.indexOf(client), 1);
    });

    // adding a callback method for the "error" event, in order to be
    // sure that any erro that occur to clients are logged and the server is no
    // aborted with an exception
    client.on('error', function(e) { console.log(e); });
});

function broadcast(message, client) {
	const cleanup = [];
  	for(let i=0; i<clientList.length; i+=1) {
    	if(client !== clientList[i]) {
      		// adding a check for the write status of the socket during
      		// the broadcast call, we can make sure that any sockets that
      		// are not available to be written don't cause exception
      		if(clientList[i].writable) { clientList[i].write(client.name + " says " + message); }
      		else {
				// make sure that any non writtable socket
        		// will be closed and removed by the list.
        		// note that we are not removing the client
        		// from the list while we are looping throug it
        		// in order to avoid side effects
        		cleanup.push(clientList[i]);
        		clientList[i].destroy();
      		}
		}
	}
	//Remove dead Nodes out of write loop to avoid trashing loop index
  	for(let i=0; i<cleanup.length; i+=1)	{
		clientList.splice(clientList.indexOf(cleanup[i]), 1)
  	}
}

chatServer.listen(9000)