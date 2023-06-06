// Import environmental variables from variables.test.env file
require('dotenv').config({ path: 'variables.test.env' });

const db = require('../database');
const server = require('../servers/http');
const chai = require('chai');
const chaiHttp = require('chai-http');
const should = chai.should();

chai.use(chaiHttp);

// Temperature /GET route
describe('/GET temperature', () => {
    it('it should GET the temperature', async () => {
        const res = await chai.request(server).get('/iot/sensors/temperature');
        res.should.have.status(200);
        res.body.should.be.a('object');
    });
});
