const { performance, PerformanceObserver } = require('perf_hooks');
const freeling = require('../'),
      errors = require('./errors'),
      Promise = require('bluebird'),
      readFile = Promise.promisify(require('fs').readFile);
const chai = require('chai'),
      expect = chai.expect,
      chaiAsPromised = require('chai-as-promised');

chai.use(chaiAsPromised);


let lang = 'ru',
    path = '/usr/local/share/freeling/',
    confPath = path + lang;
let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
            Уткнув подбородок в грудь, чтобы спастись от злого ветра,
            Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
            но все-таки впустил за собой вихрь зернистой пыли.`;


describe('promise with tokenize', function() {
  it('should successfully tokenize string', function(done) {
    freeling.tokenize(confPath + '/tokenizer.dat', text)
      .then( lw => {
        let splitter = new freeling.Splitter(confPath + '/splitter.dat');
        describe('promise with split', function() {
          it('should successfully split words into sentences', function(done) {
            freeling.split(splitter, lw)
              .then( ls => {
                  this.timeout(50000);
                  let morfo = new freeling.Morfo(path, lang);

                  morfo.setActiveOptions();
                  describe('morfoAnalyze promise', function() {
                    it('should return a Promise', function(done) {
                      let result = freeling.morfoAnalyze(morfo, ls);
                      expect(result).to.be.a('promise');
                      result
                      .then(() => { done(); })
                      .catch(() => { done(); });
                    });

                    it('promise should be rejected when number of parameters is wrong', function() {
                      return Promise
                        .all([
                          expect(freeling.morfoAnalyze()).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
                          expect(freeling.morfoAnalyze(morfo)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
                          expect(freeling.morfoAnalyze(morfo, ls, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
                        ]);
                    });

                    it('promise should be rejected when second parameter is empty', function() {
                      return Promise
                        .all([
                          expect(freeling.morfoAnalyze(morfo, [])).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
                        ]);
                    });

                    it('promise should be rejected when first parameter is not a Morfo instance or second is not an array of Sentences', function() {
                      return Promise
                        .all([
                          expect(freeling.morfoAnalyze(morfo, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
                          expect(freeling.morfoAnalyze(1, ls)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
                          expect(freeling.morfoAnalyze({}, ls)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
                        ]);
                    });

                    it('should analyze sentences', function(done) {
                      freeling.morfoAnalyze(morfo, ls)
                        .then(ls => {
                          for(let sentence of ls) {
                            let words = sentence.getSentence();
                            for(let word of words) {
                              console.log(`word : ${word.getForm()}, possible analysis: {`);
                              let analysises = word.getAnalysis();
                              for(let analysis of analysises) {
                                console.log(` ( ${analysis.getLemma()}, ${analysis.getTag()} )`);
                              }
                              console.log(`}, selected analysis: (${word.getLemma()}, ${word.getTag()})`);
                            }
                          }
                          done();
                        })
                        .catch(err => { done(new Error(err)); });
                    });
                  });
                  done();
              })
              .catch(err => { done(new Error(err)); });
          });
        });
        done();
      })
      .catch(err => { done(new Error(err)); });
  });
});
