let userList;

exports.loadUserList = function(users) {
  userList = users;
}

exports.isValidUserId = function(user) {
  return userList.indexOf(user) >= 0;
}

exports.isValidUserIdAsync = function(user, callback) {
  setTimeout(function(){ callback(userList.indexOf(user) >= 0) }, 1);
}
