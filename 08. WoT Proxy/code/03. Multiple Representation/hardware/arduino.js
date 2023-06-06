const serialport = require('serialport');
const readline = require('@serialport/parser-readline')
const values = { temperature:"0", light: "0", movement: "0" }
const portName = '/dev/cu.usbmodem1421';

const sp = new serialport(portName, {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
});

const parser = new readline();
sp.pipe(parser);

parser.on('data', function(input) {
    var res = input.split(";");
    if(res[0] == 'H')
    {
      values.temperature = res[1];
      values.movement = res[2];
      values.light = res[3];
      //console.log(res);
    }
});

module.exports = values;
