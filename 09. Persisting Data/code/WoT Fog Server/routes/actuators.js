const express = require('express');
const observer = require("node-observer");
const router = express.Router();
const resources = require('./../resources/model');

router.route('/').get(function (req, res, next) {
 req.result = resources.iot.sensors;
 next();
});

router.route('/leds').get(function (req, res, next) {
  req.result = resources.iot.actuators.leds;
  next();
});

router.route('/leds/:id').get(function (req, res, next) {
  req.result = resources.iot.actuators.leds[req.params.id];
  next();
});

// Callback for a PUT request on an LED
router.route('/leds/:id').put(function(req, res, next) {
  const selectedLed = resources.iot.actuators.leds[req.params.id];

  // Update the value of the selected LED in the model
  selectedLed.value = req.body.value;
  req.result = selectedLed;
  
  // Send information to observers
  observer.send(this, selectedLed.name , req.body.value);

  next();
});

module.exports = router;
