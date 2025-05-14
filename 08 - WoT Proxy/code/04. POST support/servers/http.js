const express = require('express');
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const resources = require('./../resources/model');
const converter = require('./../middleware/converter');

// Requires the body parser
const bodyParser = require('body-parser');

const app = express();

// Add the bodyParser to the chain
// As the bodyParse middleware get information from
// the request useful for other middleware make sure you add it first
app.use(bodyParser.json());

app.use('/iot/actuators', actuatorsRoutes);
app.use('/iot/sensors', sensorRoutes);

app.get('/iot', function (req, res) {
  res.send('This is the WoT API!')
});

app.use(converter());

module.exports = app;
