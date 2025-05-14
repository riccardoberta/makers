const express = require('express');

// We require and instantiate an Express Router to define the path to our resources
const router = express.Router();

// We require the model
const resources = require('./../resources/model');

// Create a new route for a GET request on all sensors and attach a callback function
router.route('/').get(function (req, res, next) {
  // Reply with the sensor model when this route is selected
  res.send(resources.iot.sensors);
});

// This route serves the passive infrared sensor
router.route('/pir').get(function (req, res, next) {
  res.send(resources.iot.sensors.pir);
});

// This routes serve the temperature sensor
router.route('/temperature').get(function (req, res, next) {
  res.send(resources.iot.sensors.temperature);
});

// This routes serve the light sensor
router.route('/light').get(function (req, res, next) {
  res.send(resources.iot.sensors.light);
});

// We export router to make it accessible for "requirers" of this file
module.exports = router;
