const express = require('express');
const router = express.Router();
const resources = require('./../resources/model');

router.route('/').get(function (req, res, next) {
  req.result = resources.iot.sensors;
  next();
});

// This route serves the passive infrared sensor
router.route('/pir').get(function (req, res, next) {
  req.result = resources.iot.sensors.pir;
  next();
});

// This routes serve the temperature sensor
router.route('/temperature').get(function (req, res, next) {
  req.result = resources.iot.sensors.temperature;
  next();
});

// This routes serve the light sensor
router.route('/light').get(function (req, res, next) {
  req.result = resources.iot.sensors.light;
  next();
});

module.exports = router;
