const assert = require('assert');
const loginController =  require('../../controllers/login.controller');

describe('LoginController', function () {
  describe('isValidUserId', function(){
    it('should return true if valid user id', function(){
      const isValid = loginController.isValidUserId(['abc123','xyz321'], 'abc123')
      assert.equal(isValid, true);
    });
    it('should return false if invalid user id', function(){
      const isValid = loginController.isValidUserId(['abc123','xyz321'],'abc1234')
      assert.equal(isValid, false);
    });
    it('should return false if missing user id', function(){
      const isValid = loginController.isValidUserId(['abc123','xyz321'], null)
      assert.equal(isValid, false);
    });
    it('should return false if missing user list', function(){
      const isValid = loginController.isValidUserId(null, 'xy32')
      assert.equal(isValid, false);
    });
  });
});
