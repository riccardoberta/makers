const express = require('express');
const http = require('http');

const app = express();
app.use(express.json());
const port = 3000;

const subscribers = [];

// Endpoint to subscribe to events
app.post('/subscribe', (req, res) => {
    const { url } = req.body;
    if (!url) { return res.status(400).json({ error: 'Missing URL in request body' }); }
    subscribers.push(url);
    res.status(201).json({ message: 'Subscribed successfully' });
});

// Internal function to push events to all subscribers
function publishEvent(value) {
  const data = JSON.stringify(value);

  // Send the event to all subscribers
  subscribers.forEach(subscriberURL => {

    // Parse the URL to get the hostname and port
    const { hostname, port, pathname } = new URL(subscriberURL);

    // Create an HTTP request to the subscriber
    const options = {
      hostname: hostname,
      port: parseInt(port, 10),
      path: pathname,
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
        'Content-Length': data.length
      }
    };

    // Send the request to the subscriber
    const req = http.request(options, res => { console.log(`Event sent to ${subscriberURL} - Status: ${res.statusCode}`);});
    req.on('error', err => { console.error(`Error sending to ${subscriberURL}:`, err.message); });
    req.write(data);
    req.end();
  });
}

// Simulate an event every 5 seconds
setInterval(() => {

  // Simulate a sensor event
  const event = {
    sensor: 'humidity',
    value: Math.floor(Math.random() * 100),
    timestamp: new Date().toISOString()
  };

  // Log the event and publish it to subscribers
  console.log('Publishing event:', event);
  publishEvent(event);
}, 5000);

app.listen(port, () => { console.log(`Thing server running at http://localhost:${port}`); });