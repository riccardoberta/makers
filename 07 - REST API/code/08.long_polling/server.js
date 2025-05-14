const express = require('express');
const app = express();
const port = 3000;

// The latest event to be sent to clients
let latestEvent = null;

// The list of clients waiting for events
let waitingClients = [];

// Long polling endpoint
app.get('/events', (req, res) => {
  
  // Save the response object to respond later
  waitingClients.push(res);

  // Timeout after 25 seconds to avoid broken connections
  req.setTimeout(25000, () => {
    const index = waitingClients.indexOf(res);
    if (index !== -1) waitingClients.splice(index, 1);
    res.status(204).end(); // No Content
  });
});

app.listen(port, () => { console.log(`Thing running on http://localhost:${port}`); });

// Simulate sensor generating a new event every 5 seconds
setInterval(() => {
  
  // Simulate a sensor event
  latestEvent = {
    sensor: 'humidity',
    value: Math.floor(Math.random() * 100),
    timestamp: new Date().toISOString()
  };
  console.log('New event:', latestEvent);

  // Respond to all waiting clients
  waitingClients.forEach(res => res.json(latestEvent));
  waitingClients = []; // Clear list
}, 5000);