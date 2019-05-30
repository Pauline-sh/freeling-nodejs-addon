'use strict';

const fs = require('fs'),
      path = require('path');

const getTextFromFile = (filename) => {
  return new Promise((resolve, reject) => {
    let filePath = path.join(__dirname, filename);
    fs.readFile(filePath, 'utf-8', (error, data) => {
      if (!error) {
        resolve(data);
      } else {
        reject(error);
      }
    });
  });
};

module.exports.getTextFromFile = getTextFromFile;
