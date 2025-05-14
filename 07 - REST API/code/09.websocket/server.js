const WebSocket = require('ws');

// Create a WebSocket server
const wss = new WebSocket.Server({ port: 3000 });

// Array to hold connected clients
let clients = [];

// Handle WebSocket connections
wss.on('connection', ws => {
  console.log('Client connected');

  // Add the new client to the array
  clients.push(ws);

  // Manage closing connections
  ws.on('close', () => {
    console.log('Client disconnected');
    clients = clients.filter(client => client !== ws);
  });
});

// Broadcast a simulated sensor event every 5 seconds
setInterval(() => {

  // Simulate a sensor event
  const event = {
    sensor: 'humidity',
    value: Math.floor(Math.random() * 100),
    timestamp: new Date().toISOString()
  };
  console.log('Broadcasting:', event);
  
  // Send the event to all connected clients
  const message = JSON.stringify(event);
  clients.forEach(ws => {
    if (ws.readyState === WebSocket.OPEN) { ws.send(message); }
  });

}, 5000);