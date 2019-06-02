const freeling = require('../freeling/freeling');
const jm = require('js-meter');
const utils = require('./utils');

const cnfPath = '/usr/local/share/freeling/';
const cnfLang = 'ru';
const cnfTokenizer = '/tokenizer.dat';
const cnfSplitter = '/splitter.dat';
const isPrint = true;
const isKb = true;

let tokenizer = new freeling.Tokenizer(cnfPath + cnfLang + cnfTokenizer);
let splitter = new freeling.Splitter(cnfPath + cnfLang + cnfSplitter);

const constructorPerformanceStart = new jm({ isPrint, isKb });
let morfo = new freeling.Morfo(cnfPath, cnfLang);
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

        Promise.all([splitter.split(lw1658tokens), splitter.split(lw8368tokens)])
          .then((sentenceLists) => {
            const ls1658tokens = sentenceLists[0];
            const ls8368tokens = sentenceLists[1];

            const analyzePerformanceStart = new jm({ isPrint, isKb });
            morfo.analyze(ls1658tokens)
              .then((result) => {
                console.log(`=== analyze 1658 performance ===`);
                const analyzePerformance = analyzePerformanceStart.stop();
              })
            morfo.analyze(ls8368tokens)
              .then((result) => {
                console.log(`=== analyze 8368 performance ===`);
                const analyzePerformance = analyzePerformanceStart.stop();
              })
          })
      })
  })
  .catch((err) => {
    console.error(err);
  });
