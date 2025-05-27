const resources = require('./../resources/model');
const mongoose = require('mongoose');
const MeasurementTypes = require('./../models/measurementTypes');
const Measurement = mongoose.model('Measurement');
let interval;
const model = resources.iot.sensors.light;
const pluginName = resources.iot.sensors.light.name;
const unit = resources.iot.sensors.light.unit;
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
  if (localParams.simulate) { clearInterval(interval); } 
  else { sensor.unexport(); }
  console.info('%s plugin stopped!', pluginName);
};

// Require and connect the actual hardware driver and configure it
function connectHardware() {
  const arduino = require('./../hardware/arduino');
  interval = setInterval(function () { model.value = arduino.light; }, localParams.frequency);
  console.info('Hardware %s sensor started!', pluginName);
};

// Allows the plugin to be in simulation mode. This is very useful when developing
// or when you want to test your code on a device with no sensors connected, such as your laptop
function simulate() {
  interval = setInterval(function () { 
    model.value += 1;
    (new Measurement({ type:MeasurementTypes.light, value: model.value })).save(); 
    showValue(); 
  }, localParams.frequency);
  console.info('Simulated %s sensor started!', pluginName);
};

function showValue() { console.info('%s value = %s %s', pluginName, model.value, unit); };
