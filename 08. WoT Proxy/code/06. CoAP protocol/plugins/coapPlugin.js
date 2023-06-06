const resources = require('./../resources/model');

const model = resources.iot.sensors.co2;
const pluginName = resources.iot.sensors.co2.name;
const unit = resources.iot.sensors.co2.unit;

let interval, pollInterval;
let localParams = {'simulate': false, 'frequency': 5000};

function connectHardware() {
  
  // Require the CoAP and BL library, a Buffer helper
  const coap = require('coap');
  const bl = require('bl');

  // Create a sensor object and give it a read function
  var sensor = {
    // The read function wraps a coap over UDP request with the enclosed parameters; 
    // replace localhost with the IP of the machine you’re simulating the CoAP 
    // device from (e.g., your laptop)
    read: function () {
      coap
        .request({
          host: 'localhost',
          port: 5683,
          pathname: '/co2',
          options: {'Accept': 'application/json'}
        })
        // When CoAP device sends the result, the on response event is triggered
        .on('response', function (res) {
          console.info('CoAP response code', res.code);
          if (res.code !== '2.05')
            console.log("Error while contacting CoAP service: %s", res.code);
          // Fetch the results and update the model  
          res.pipe(bl(function (err, data) {
            var json = JSON.parse(data);
            model.value = json.co2;
            showValue();
          }));
        })
        .end();
    }
  };
  
  // Poll the CoAP device for new CO2 readings on a regular basis
  pollInterval = setInterval(function () {
    sensor.read();
  }, localParams.frequency);
};

exports.start = function (params, app) {
  localParams = params;

  if (params.simulate) {
    simulate();
  } else {
    connectHardware();
  }
};

exports.stop = function () {
  if (params.simulate) {
    clearInterval(interval);
  } else {
    clearInterval(pollInterval);
  }
  console.info('%s plugin stopped!', pluginName);
};

function simulate() {
  interval = setInterval(function () {
    model.value = Math.floor(Math.random() * 1000);
    showValue();
  }, localParams.frequency);
  console.info('Simulated %s sensor started!', pluginName);
};

function showValue() {
  console.info('CO2 Level: %s ppm', model.value);
};
