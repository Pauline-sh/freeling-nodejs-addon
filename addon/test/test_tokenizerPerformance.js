const freeling = require('../freeling/freeling');
const process = require('process'),
      fs = require('fs'),
      path = require('path'),
      jm = require('js-meter');
const cnfPath = '/usr/local/share/freeling/ru/';
const cnfTokenizer = 'tokenizer.dat';


const getTextFromFile = (filename) => {
  return new Promise((resolve, reject) => {
    let filePath = path.join(__dirname, filename);
    fs.readFile(filePath, 'utf-8', (error, data) => {
      if(!error) {
        resolve(data);
      } else {
        reject(error);
      }
    });
  });
}

getTextFromFile('text1658tokens.txt')
  .then((testText) => {
    const isPrint = true
    const isKb = true
    const m = new jm({ isPrint, isKb });

    let tokenizer = new freeling.Tokenizer(cnfPath + cnfTokenizer);

    tokenizer.tokenize(testText)
      .then((lw) => {
        const meter = m.stop();
        
        console.log(`Total performance data: ${meter}`);
      });
  })
  .catch((error) => {
    console.error(error);
  });
