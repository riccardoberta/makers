const http = require('http');
const assert = require('assert');

// An option object containing a list of properties
const opts = {
  host: 'localhost',
  port: 8000,
  path: '/send',
  method: 'POST',
  headers: {'content-type':'application/json'}
}

// We create an HTTP request, using the option object
const req = http.request(opts, function(res){
  res.setEncoding('utf8');
  let data = '';
  res.on('data', function(d) { data += d; })
  res.on('end', function() { assert.strictEqual(data, '{"status":"ok","message":"Tweet received"}'); })
})

// write some data to the server
req.write('{"tweety":"test"}');
req.end();
