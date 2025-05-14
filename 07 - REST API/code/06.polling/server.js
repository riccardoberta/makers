const express = require('express');

const app = express();
const port = 3000;

// Simulated sensor value
let sensorValue = 0;

// REST endpoint to get sensor value
app.get('/sensor', (req, res) => {
  res.json({ value: sensorValue });
});

app.listen(port, () => { console.log(`Web Thing listening at http://localhost:${port}`); });

// Simulate sensor updating value every 5 seconds
setInterval(() => {
    sensorValue = Math.floor(Math.random() * 100);
    console.log(`Sensor updated: ${sensorValue}`);
  }, 5000);