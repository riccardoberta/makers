const http = require('http');

function pollSensor() {
  const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/sensor',
    method: 'GET',
  };

  const req = http.request(options, res => {
    let data = '';
    res.on('data', chunk => data += chunk);
    res.on('end', () => {
      try {
        const parsed = JSON.parse(data);
        console.log(`Polled Sensor Value: ${parsed.value}`);
      } 
      catch (err) { console.error('Error parsing response:', err.message);}
    });
  });

  req.on('error', err => { console.error('Request error:', err.message); });

  req.end();
}

// Poll every 2 seconds
setInterval(pollSensor, 2000);