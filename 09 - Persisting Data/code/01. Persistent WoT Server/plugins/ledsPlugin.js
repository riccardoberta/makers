const resources = require('./../resources/model');
let observer = require("node-observer");

const model1 = resources.iot.actuators.leds['1'];
const model2 = resources.iot.actuators.leds['2'];
let interval;
const pluginName = "Leds"
let localParams = {'simulate': false, 'frequency': 2000};

exports.start = function (params) {
  localParams = params;
  // Observe the model for the LEDs
  observe(model1);
  observe(model2);
  if (localParams.simulate) { simulate(); } 
  else { connectHardware(); }
};

exports.stop = function () {
  clearInterval(interval);
  console.info('%s plugin stopped!', pluginName);
};

function observe(what) { observer.subscribe(this, what.name, function(who, data) { switchOnOff(what.name, data); }); };

function switchOnOff(name, value) {
  console.info('Change detected by plugin for %s = %s', name, value);
  if (!localParams.simulate) {
    const arduino = require('./../hardware/arduino');
    arduino.send(name, value);
    console.info('Changed value of %s to %s', name, value);
  }
};

function connectHardware() { console.info('Hardware %s actuator started!', pluginName); };

function simulate() {
  interval = setInterval(function () {
    // Switch value on a regular basis
    if (model1.value) { model1.value = false; } 
    else { model1.value = true; }
  }, localParams.frequency);
  console.info('Simulated %s actuator started!', pluginName);
};
