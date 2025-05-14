exports.isValidUserId =  function(userList, user) {
  if(!userList) return false;
  return userList.indexOf(user) >= 0;
}
