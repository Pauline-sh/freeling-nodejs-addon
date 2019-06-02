const freeling = require('../freeling/freeling');
const jm = require('js-meter');
const utils = require('./utils');

const cnfPath = '/usr/local/share/freeling/ru/';
const cnfTokenizer = 'tokenizer.dat';
const cnfSplitter = 'splitter.dat';
const isPrint = true;
const isKb = true;

let tokenizer = new freeling.Tokenizer(cnfPath + cnfTokenizer);

const constructorPerformanceStart = new jm({ isPrint, isKb });
let splitter = new freeling.Splitter(cnfPath + cnfSplitter);
console.log(`=== constructor performance ===`);
const constructorPerformance = constructorPerformanceStart.stop();

Promise.all([utils.getTextFromFile('text1658tokens.txt'), utils.getTextFromFile('text8368tokens.txt')])
  .then((texts) => {
    const text1658tokens = texts[0];
    const text8368tokens = texts[1];

    Promise.all([tokenizer.tokenize(text1658tokens), tokenizer.tokenize(text8368tokens)])
      .then((wordLists) => {
        const lw1658tokens = wordLists[0];
        const lw8368tokens = wordLists[1];

        let splitPerformanceStart = new jm({ isPrint, isKb });
        splitter.split(lw1658tokens)
          .then((ls) => {
            console.log(`=== split 1658 tokens performance ===`);
            let splitPerformance = splitPerformanceStart.stop();
          });
        splitter.split(lw8368tokens)
          .then((ls) => {
            console.log(`=== split 8368 tokens performance ===`);
            let splitPerformance = splitPerformanceStart.stop();
          });
        splitPerformanceStart = new jm({ isPrint, isKb });
        Promise.all([splitter.split(lw1658tokens), splitter.split(lw8368tokens)])
          .then((results) => {
            console.log(`=== split 1658 and 8368 tokens performance ===`);
            let splitPerformance = splitPerformanceStart.stop();
          })
      })
  })
  .catch((err) => {
    console.error(err);
  });
