var express = require('express');

var router = express.Router();
var resources = require('./../resources/model');

router.route('/').get(function (req, res, next) {
  req.result = resources.iot.sensors;
  next();
});

router.route('/pir').get(function (req, res, next) {
  req.result = resources.iot.sensors.pir;
  next();
});

router.route('/temperature').get(function (req, res, next) {
  req.result = resources.iot.sensors.temperature;
  next();
});

router.route('/light').get(function (req, res, next) {
  req.result = resources.iot.sensors.light;
  next();
});

// This routes serve the co2 sensor
router.route('/co2').get(function (req, res, next) {
  req.result = resources.iot.sensors.co2;
  next();
});

module.exports = router;
