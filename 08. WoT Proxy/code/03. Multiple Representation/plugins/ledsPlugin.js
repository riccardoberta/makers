const resources = require('./../resources/model');

let interval;
const model1 = resources.iot.actuators.leds['1'];
const model2 = resources.iot.actuators.leds['2'];
const pluginName = "Leds"
let localParams = {'simulate': false, 'frequency': 2000};

exports.start = function (params) {
  localParams = params;
  if (localParams.simulate) { simulate(); } 
  else { connectHardware(); }
};

exports.stop = function () {
  clearInterval(interval);
  console.info('%s plugin stopped!', pluginName);
};

function connectHardware() { console.info('Hardware %s actuator started!', pluginName); };

function simulate() {
  interval = setInterval(function () {
    if (model1.value) { model1.value = false; } 
    else { model1.value = true; }
    if (model2.value) { model2.value = false; } 
    else { model2.value = true; }
  }, localParams.frequency);
  console.info('Simulated %s actuator started!', pluginName);
};
