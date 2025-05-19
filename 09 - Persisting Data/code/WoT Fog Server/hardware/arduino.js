const serialport = require('serialport');
const portName = '/dev/cu.usbmodem144301';

const sp = new serialport(portName, {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false,
    parser: new serialport.parsers.Readline("\r\n")
});

sp.on('data', function(input) {
    var res = input.toString().split(";");
    if(res[0] == 'H')
    {
      values.temperature = res[1];
      values.movement = res[2];
      values.light = res[3];
      //console.log(res);
    }
});

const values = { temperature:"0", light: "0", movement: "0", 
               send: function(led, data){
                    if(led=="LED 1" && data==false) sp.write("0");
                    if(led=="LED 1" && data==true) sp.write("1");
                    if(led=="LED 2" && data==false) sp.write("2");
                    if(led=="LED 2" && data==true) sp.write("3");
                }}

module.exports = values;