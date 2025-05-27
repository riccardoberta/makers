const resources = require('./../resources/model');
const observer = require("node-observer");
const mongoose = require('mongoose');
const MeasurementTypes = require('./../models/measurementTypes');
const Measurement = mongoose.model('Measurement');

let interval;
const model = resources.iot.sensors.temperature;
const pluginName = resources.iot.sensors.temperature.name;
const unit = resources.iot.sensors.temperature.unit;
let localParams = {'simulate': true, 'frequency': 2000};

// Starts the plugin, should be accessible from other
// files so we export them
exports.start = function (params) {
  localParams = params;
  if (localParams.simulate) { simulate(); } 
  else { connectHardware(); }
};

// Stop the plugin, should be accessible from other
// files so we export them
exports.stop = function () {
  clearInterval(interval);
  console.info('%s plugin stopped!', pluginName);
};

// Require and connect the actual hardware driver and configure it
function connectHardware() {
  var arduino = require('./../hardware/arduino');
  interval = setInterval(function () { model.value = arduino.temperature; }, localParams.frequency);
  console.info('Hardware %s sensor started!', pluginName);
};

// Allows the plugin to be in simulation mode. This is very useful when developing
// or when you want to test your code on a device with no sensors connected, such as your laptop
function simulate() {
  interval = setInterval(function () { 
    model.value += 1; 
    observer.send(this, model.name , model.value);
    (new Measurement({ type:MeasurementTypes.temperature, value: model.value })).save();
    showValue(); 
  }, localParams.frequency);
  console.info('Simulated %s sensor started!', pluginName);
};

function showValue() { console.info('%s value = %s %s', pluginName, model.value, unit); };
