const express = require('express');
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const resources = require('./../resources/model');

// Requires the converter
const converter = require('./../middleware/converter');

// Creates an application with the Express framework
// this wraps an HTTP server
const app = express();

// Binds your routes to the Express application
// bind them to /pi/actuators/... and /pi/sensors/...
app.use('/iot/actuators', actuatorsRoutes);
app.use('/iot/sensors', sensorRoutes);

// Create a default route for /iot
app.get('/iot', function (req, res) {
  res.send('This is the WoT API!')
});

// Add the converter to the chain
// As the converter middleware responds to the client
// make sure you add it last, after app.get('iot') or it
// will simply bypass any other middleware!
app.use(converter());

module.exports = app;
