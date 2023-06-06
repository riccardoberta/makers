// Require the two modules and instantiate a MessagePack encoder
const msgpack = require('msgpack5')();
const json2html = require('node-json2html');

const encode = msgpack.encode;

// In Express, a middleware is usually a function returning a function
module.exports = function() {
  return function (req, res, next) {
    console.info('Representation converter middleware called!');

    // Check if the previous middleware left a result in req.result
    if (req.result) {
      // Read the request header and check if the client requested HTML
      if (req.accepts('html')) {
        console.info('HTML representation selected!');
        // If HTML was requested, use json2html to transform the JSON into simple HTML
        const transform = {'tag': 'div', 'html': '${name} : ${value}'};
        res.send(json2html.transform(req.result, transform));
        return;
      }
      // Read the request header and check if the client requested MessagePack
      if (req.accepts('application/x-msgpack')) {
        console.info('MessagePack representation selected!');
        // Encode the JSON into MessagePack using the encoder
        res.type('application/x-msgpack');
        res.send(encode(req.result));
        return;
      }
      // For all other formats, default to JSON
      console.info('Defaulting to JSON representation!');
      res.send(req.result);
      return;
    }
    else {
      // If no result was present in req.result, there’s not much you can do, so call the next middleware
      next();
    }
  }
};
