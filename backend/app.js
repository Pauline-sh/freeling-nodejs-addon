const express = require('express');
const bodyParser = require('body-parser');
const routes = require('./routes/index');
const expressValidator = require('express-validator');
const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(expressValidator());
app.use('/', routes);
app.use((error, req, res, next) => {
    res.status(400).json({
      error: error.message
    });
});

module.exports = app;