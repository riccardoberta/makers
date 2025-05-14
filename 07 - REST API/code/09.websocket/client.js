const WebSocket = require('ws');

// Create a WebSocket client
const ws = new WebSocket('ws://localhost:3000');

// Handle WebSocket events
ws.on('open', () => { console.log('Connected to WebSocket server'); });

ws.on('message', data => {
  const event = JSON.parse(data);
  console.log('Received event:', event);
});

ws.on('close', () => { console.log('Disconnected from server'); });

ws.on('error', err => { console.error('WebSocket error:', err.message); });