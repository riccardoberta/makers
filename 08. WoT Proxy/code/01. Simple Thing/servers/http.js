// Requires the Express framework, your routes, and the model
const express = require('express');
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const resources = require('./../resources/model');

// Creates an application with the Express framework
// this wraps an HTTP server
const app = express();

// Binds your routes to the Express application
// bind them to /pi/actuators/... and /pi/sensors/...
app.use('/iot/actuators', actuatorsRoutes);
app.use('/iot/sensors', sensorRoutes);

// Create a default route for /pi
app.get('/iot', function (req, res) {
  res.send('This is the WoT API!')
});

// We export router to make it accessible for "requirers" of this file
module.exports = app;
