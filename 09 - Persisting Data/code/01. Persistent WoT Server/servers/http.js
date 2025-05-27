const express = require('express');
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const measurementRoutes = require('./../routes/measurements');
const converter = require('./../middleware/converter');
const bodyParser = require('body-parser');

const app = express();

app.use(bodyParser.json());

app.use('/iot/actuators', actuatorsRoutes);
app.use('/iot/sensors', sensorRoutes);
app.use('/iot/measurements', measurementRoutes);

app.get('/iot', function (req, res) { res.send('This is the WoT API!') });

app.use(converter());

module.exports = app;
