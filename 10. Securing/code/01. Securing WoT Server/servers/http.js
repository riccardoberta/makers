const express = require('express');
const actuatorsRoutes = require('./../routes/actuators');
const sensorRoutes = require('./../routes/sensors');
const measurementRoutes = require('./../routes/measurements');
const converter = require('./../middleware/converter');
const bodyParser = require('body-parser');

// Securing
const https = require('https');
const fs = require('fs');
const cert_file = './resources/caCert.pem'; // The certificate
const key_file = './resources/privateKey.pem'; // The private key
const passphrase = 'pippo';  // The password of the private key
const config = { key: fs.readFileSync(key_file), cert: fs.readFileSync(cert_file), passphrase: passphrase };
const auth = require('./../middleware/auth');

const app = express();

app.use(bodyParser.json());

app.use(auth());

app.use('/iot/actuators', actuatorsRoutes);
app.use('/iot/sensors', sensorRoutes);
app.use('/iot/measurements', measurementRoutes);

app.get('/iot', function (req, res) { res.send('This is the WoT API!') });

app.use(converter());

// Add HTTPS support
const server = https.createServer(config, app);

module.exports = server;
