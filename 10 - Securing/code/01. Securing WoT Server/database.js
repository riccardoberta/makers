const mongoose = require('mongoose');
const mongoosePaginate = require('mongoose-paginate');

mongoose.Promise = global.Promise; 
mongoose.connect(process.env.DATABASE);

mongoose.connection.on('error', (err) => {
  console.error('Database connection error '+ err.message);
});

mongoosePaginate.paginate.options = { 
  lean: false,
};

require('./models/measurementSchema');
