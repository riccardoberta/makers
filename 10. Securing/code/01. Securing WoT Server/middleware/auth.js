const keys = require('../resources/auth');

module.exports = function()  {
  return function (req, res, next) {
    console.log(req.method + " " + req.path);
    
    // check header or url parameters or post parameters for token
    const token = req.body.token || req.get('authorization') || req.query.token;
    console.log(req.params);
      
    // If no token provided, return 401 UNAUTHORIZED
    if (!token) { return res.status(401).send({success: false, message: 'API token missing.'}); } 
    // If token is not a valid API key, return 403 FORBIDDEN
    else if (token != keys.apiToken) { return res.status(403).send({success: false, message: 'API token invalid.'}); } 
    // If everything is good, save to request for use in other routes
    else { next(); }
  }
};
