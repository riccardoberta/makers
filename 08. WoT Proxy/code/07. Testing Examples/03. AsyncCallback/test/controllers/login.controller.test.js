const assert = require('assert');
const loginController =  require('../../controllers/login.controller');

describe('LoginController', function () {
  describe('isValidUserIdAsync', function(){
    it('should return true if valid user id', function(){
      loginController.isValidUserIdAsync(['abc123','xyz321'], 'abc123',
        function(isValid){ assert.equal(isValid, true); ; });
      });
  });
});
