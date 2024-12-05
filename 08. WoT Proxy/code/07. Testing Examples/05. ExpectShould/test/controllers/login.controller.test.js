const assert = require('assert');
const loginController =  require('../../controllers/login.controller');

const expect = require('chai').expect;
const should = require('chai').should();

beforeEach('Setting up the userList', function(){
  loginController.loadUserList(['abc123','xyz321']);
});

describe('LoginController', function () {
  describe('isValidUserId', function(){
    it('should return true if valid user id', function(){
      const isValid = loginController.isValidUserId('abc123')
      //assert.equal(isValid, true);
      expect(isValid).to.be.true;
    });
    it('should return false if invalid user id', function(){
      const isValid = loginController.isValidUserId('abc1234')
      //assert.equal(isValid, false);
      isValid.should.equal(false);
    });
  });

  describe('isValidUserIdAsync', function(){
    it('should return true if valid user id', function(done){
      loginController.isValidUserIdAsync('abc123',
      function(isValid){
          //assert.equal(isValid, true);
          isValid.should.equal(true);
          done();
      });
    });
  });

});
