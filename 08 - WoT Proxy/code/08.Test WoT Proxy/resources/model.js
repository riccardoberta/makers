// We load the entire data model from other files (here only resources.json)
const resources = require('./resources.json');

// We export the resources to make it accessible for "requirers" of this file
module.exports = resources;
