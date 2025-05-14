const should = require('chai').should();

describe('Object Test', function(){
  it('should have property name', function(){
    const car = { name:'Compass', Maker:'Jeep' }
    car.should.have.property('name');
  });

  it('should have property name with value Compass', function(){
    const car = { name:'Compass', Maker:'Jeep' }
    car.should.have.property('name').equal('Compass');
  });

  it('should compare objects', function(){
    const car = {name:'Compass', Maker:'Jeep'}
    const car1 = {name:'Compass', Maker:'Jeep'}
    car.should.deep.equal(car1);
  });
});
