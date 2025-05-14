const server = require('../servers/http');
const chai = require('chai');
const chaiHttp = require('chai-http');
const should = chai.should();

chai.use(chaiHttp);

// Temperature /GET route
describe('/GET temperature', () => {
    it('it should GET the temperature', async () => {
        const res = await chai.request(server).get('/iot/sensors/temperature');
        res.should.have.status(404);
        res.body.should.be.a('object');
    });
});
