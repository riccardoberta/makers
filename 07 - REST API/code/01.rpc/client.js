const http = require('http');

// Client-side code to call the RPC method
function remoteAdd(a, b) {
  
    // Create a JSON-RPC request
    const data = JSON.stringify({
        method: 'add',
        params: [a, b]
    });

    // Set up the HTTP request options
    const options = {
        hostname: 'localhost',
        port: 3000,
        path: '/rpc',
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
            'Content-Length': Buffer.byteLength(data)
        }
    };

    // Make the HTTP request
    const req = http.request(options, res => {
        let body = '';

        res.on('data', chunk => {
            body += chunk;
        });

        res.on('end', () => {
            try {
                const parsed = JSON.parse(body);
                if (res.statusCode === 200) { console.log('Result from RPC call:', parsed.result); } 
                else { console.error('RPC Error:', parsed.error); }
            } 
            catch (err) { console.error('Error parsing response:', err.message); }
        });
    });

    req.on('error', err => { console.error('Request error:', err.message);});

    req.write(data);
    req.end();
}

// Example of calling the remote method
remoteAdd(7, 5);
