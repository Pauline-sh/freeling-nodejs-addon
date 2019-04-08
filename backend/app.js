const express = require('express');
const bodyParser = require('body-parser');
const routes = require('./routes/index');
const expressValidator = require('express-validator');
const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(expressValidator());

app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.use('/', routes);

app.use((error, req, res, next) => {
    res.status(400).json({
      error: error.message
    });
});

module.exports = app;
