const fs = require('fs');

const server = require('http').createServer();

server.on('request', (req, res) => {
	res.writeHead(200, {'Content-Type': 'text/plain'});
	const stream  = fs.createReadStream('./big.file');
	stream.pipe(res);
});

server.listen(8000);