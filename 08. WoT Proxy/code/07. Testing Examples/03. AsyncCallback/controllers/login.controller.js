exports.isValidUserIdAsync = function(userList, user, callback) {
  setTimeout(function(){ callback(userList.indexOf(user) >= 0) }, 5);
}