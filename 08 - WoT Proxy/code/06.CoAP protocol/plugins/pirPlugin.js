const resources = require('./../resources/model');

let interval;
const model = resources.iot.sensors.pir;
const pluginName = resources.iot.sensors.pir.name;
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
  interval = setInterval(function () { model.value = arduino.movement; }, localParams.frequency);
  console.info('Hardware %s sensor started!', pluginName);
};

// Allows the plugin to be in simulation mode. This is very useful when developing
// or when you want to test your code on a device with no sensors connected, such as your laptop
function simulate() {
  interval = setInterval(function () {
    if (model.value) { model.value = false; } 
    else { model.value = true; }
    showValue();
  }, localParams.frequency);
  console.info('Simulated %s sensor started!', pluginName);
};

function showValue() { console.info(model.value ? 'there is someone!' : 'not anymore!'); };
