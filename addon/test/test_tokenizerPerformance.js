const freeling = require('../freeling/freeling');
const jm = require('js-meter');
const utils = require('./utils');

const cnfPath = '/usr/local/share/freeling/ru/';
const cnfTokenizer = 'tokenizer.dat';
const isPrint = true;
const isKb = true;

const constructorPerformanceStart = new jm({ isPrint, isKb });
let tokenizer = new freeling.Tokenizer(cnfPath + cnfTokenizer);
console.log(`=== constructor performance ===`);
const constructorPerformance = constructorPerformanceStart.stop();

Promise.all([utils.getTextFromFile('text1658tokens.txt'), utils.getTextFromFile('text8368tokens.txt')])
  .then((texts) => {
    const text1658tokens = texts[0];
    const text8368tokens = texts[1];

    let tokenizePerformanceStart1 = new jm({ isPrint, isKb });
    tokenizer.tokenize(text1658tokens)
      .then((lw) => {
        console.log(`=== tokenize 1658 tokens performance ===`);
        let tokenizePerformance1 = tokenizePerformanceStart1.stop();
      });

    let tokenizePerformanceStart2 = new jm({ isPrint, isKb });
    tokenizer.tokenize(text8368tokens)
      .then((lw) => {
        console.log(`=== tokenize 8368 tokens performance ===`);
        tokenizePerformance2 = tokenizePerformanceStart2.stop();
      });
  })
  .catch((err) => {
    console.error(err);
  });
