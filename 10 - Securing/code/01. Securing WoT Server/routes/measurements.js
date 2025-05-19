const express = require('express');
const router = express.Router();
const mongoose = require('mongoose');
const Measurement = mongoose.model('Measurement');

router.route('/').get(async function (req, res, next) {
    try {
        if (!req.query.page) req.query.page = '1';
        if (!req.query.limit) req.query.limit = '10';
        if (!req.query.filter) req.query.filter = '{}';
        if (!req.query.sort) req.query.sort = "{ \"timestamp\": \"desc\" }";
        if (!req.query.select) req.query.select = '{}';
        if (req.query.filter.startsWith("[")) { req.query.filter = "{ \"$or\": " + req.query.filter + " }" };
        const filter = JSON.parse(req.query.filter);
        const options = {
            select: JSON.parse(req.query.select),
            sort: JSON.parse(req.query.sort),
            page: parseInt(req.query.page),
            limit: parseInt(req.query.limit)
        }
        const measurements = await Measurement.paginate(filter, options);
        req.result = measurements;
        next();
    }
    catch (err) { return res.status(500).json({ status: 500, message: err.message }) };
});

module.exports = router;
