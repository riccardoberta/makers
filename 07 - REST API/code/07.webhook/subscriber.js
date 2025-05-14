const express = require('express');
const http = require('http');
const app = express();
const port = 5001;

app.use(express.json());

// Webhook endpoint to receive events
app.post('/webhook', (req, res) => {
  console.log('Received event:', req.body);
  res.sendStatus(204);
});

// Server to listen for incoming events
app.listen(port, () => {
  console.log(`Subscriber listening on http://localhost:${port}/webhook`);

  // Automatically subscribe to the Thing
  const data = JSON.stringify({ url: `http://localhost:${port}/webhook` });

  const options = {
    hostname: 'localhost',
    port: 3000,
    path: '/subscribe',
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Content-Length': data.length
    }
  };

  const req = http.request(options, res => { console.log(`Subscribed to Thing - Status: ${res.statusCode}`);});
  req.on('error', err => { console.error('Error subscribing:', err.message); });
  req.write(data);
  req.end();
});