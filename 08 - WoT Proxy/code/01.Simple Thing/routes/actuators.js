const express = require('express');

// We require and instantiate an Express Router to define the path to our resources
const router = express.Router();

// We require the model
const resources = require('./../resources/model');

// Create a new route for a GET request
router.route('/').get(function (req, res, next) {
 // Reply with the actuators model when this route is selected
 res.send(resources.iot.actuators);
});

// This route serves a list of LEDs
router.route('/leds').get(function (req, res, next) {
  res.send(resources.iot.actuators.leds);
});

// With :id we inject a variable in the path which will be the LED number
router.route('/leds/:id').get(function (req, res, next) {
  // The path variables are accessible via req.params.id
  // we use this to select the right object in our model and return it
  res.send(resources.iot.actuators.leds[req.params.id]);
});

// We export router to make it accessible for "requirers" of this file
module.exports = router;
