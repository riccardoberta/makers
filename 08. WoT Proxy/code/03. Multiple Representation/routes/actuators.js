const express = require('express');

const router = express.Router();
const resources = require('./../resources/model');

router.route('/').get(function (req, res, next) {
  // We assign the results to a new property of the req object
  // that we pass along from middleware to middleware
 req.result = resources.iot.sensors;

 // We then call the next middleware.
 // The framework will ensure the next middleware gets access to req
 // (including the req.result) and res.
 next();
});

// This route serves a list of LEDs
router.route('/leds').get(function (req, res, next) {
  req.result = resources.iot.actuators.leds;
  next();
});

// With :id we inject a variable in the path which will be the LED number
router.route('/leds/:id').get(function (req, res, next) {
  req.result = resources.iot.actuators.leds[req.params.id];
  next();
});

module.exports = router;
