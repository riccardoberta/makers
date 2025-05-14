const http = require('http');

// Create a polling request
function poll() {
  const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/events',
    method: 'GET'
  };

  // Send the request to the server
  const req = http.request(options, res => {
    let data = '';

    res.on('data', chunk => data += chunk);

    // Handle the end of the response
    res.on('end', () => {
      if (res.statusCode === 200 && data) {
        const event = JSON.parse(data);
        console.log('Received event:', event);
      } 
      else { console.log('No new event (timeout).'); }
      
      // Immediately reconnect after receiving response
      poll();
    });
  });

  req.on('error', err => {
    console.error('Polling error:', err.message);
    // Retry after delay
    setTimeout(poll, 2000); 
  });

  req.end();
}

// Start polling loop
poll(); 
