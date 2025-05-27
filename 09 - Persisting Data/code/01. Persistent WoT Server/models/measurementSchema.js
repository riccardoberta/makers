const mongoose = require('mongoose');

const measurementSchema = new mongoose.Schema({ 
    type: { type: String, required: true },
    value: { type: String },
    timestamp: { type: Date, default: Date.now }
});

measurementSchema.index({ type: 1 });
measurementSchema.plugin(require('mongoose-paginate'));

module.exports = mongoose.model('Measurement', measurementSchema);
