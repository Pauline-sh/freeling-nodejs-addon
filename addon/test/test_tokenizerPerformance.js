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

const overallPerformanceStart = new jm({ isPrint, isKb });
Promise.all([utils.getTextFromFile('text1658tokens.txt'), utils.getTextFromFile('text8368tokens.txt')])
  .then((texts) => {
    const text1658tokens = texts[0];
    const text8368tokens = texts[1];

    let tokenizePerformanceStart = new jm({ isPrint, isKb });
    tokenizer.tokenize(text1658tokens)
      .then((lw) => {
        console.log(`=== tokenize 1658 tokens performance 1 ===`);
        let tokenizePerformance = tokenizePerformanceStart.stop();
      });
    tokenizer.tokenize(text1658tokens)
      .then((lw) => {
        console.log(`=== tokenize 1658 tokens performance 2 ===`);
        let tokenizePerformance = tokenizePerformanceStart.stop();
      });
    tokenizer.tokenize(text8368tokens)
      .then((lw) => {
        console.log(`=== tokenize 8368 tokens performance 1 ===`);
        let tokenizePerformance = tokenizePerformanceStart.stop();
      });
    tokenizer.tokenize(text8368tokens)
      .then((lw) => {
        console.log(`=== tokenize 8368 tokens performance 2 ===`);
        let tokenizePerformance = tokenizePerformanceStart.stop();
      });
    Promise.all([tokenizer.tokenize(text1658tokens), tokenizer.tokenize(text8368tokens)])
    .then((results) => {
      console.log(`=== tokenize 1658 and 8368 tokens performance ===`);
      let tokenizePerformance = tokenizePerformanceStart.stop();
    })
  })
  .catch((err) => {
    console.error(err);
  });
