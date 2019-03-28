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
    let tokenizer = new freeling.Tokenizer(confPath + '/tokenizer.dat');
    freeling.tokenize(tokenizer, text)
      .then( lw => {
        let splitter = new freeling.Splitter(confPath + '/splitter.dat');
        describe('promise with split', function() {
          it('should successfully split words into sentences', function(done) {
            freeling.split(splitter, lw)
              .then( ls => {
                describe('Morfo', function() {

                  it('should be a function', function() {
                    expect(freeling.Morfo).to.be.a('function');
                  });

                  it('should synchronously throw when doesn\'t have 2 parameters', function() {
                    expect(() => { new freeling.Morfo(1); }).to.throw(TypeError,
                      errors.WRONG_ARGUMENT_NUMBER);
                  });

                  it('should synchronously throw when parameters are not strings', function() {
                    expect(() => { new freeling.Morfo(1, 2); }).to.throw(TypeError,
                      errors.WRONG_ARGUMENT_TYPE);
                  });

                  it('should return an instance of Morfo when the arguments are strings', function() {
                    try {
                      this.timeout(50000);
                      let morfo = new freeling.Morfo(path, lang);
                      expect(morfo).to.be.an.instanceof(freeling.Morfo);

                      describe('setActiveOptions', function() {
                        it('should be a function', function() {
                          expect(morfo.setActiveOptions).to.be.a('function');
                        });

                        it('should set default active options when no args are provided', function() {
                          let result = morfo.setActiveOptions();
                          expect(result).to.be.a('undefined');
                        });

                        it('should throw when opts object doesn\'t contain all required properties', function() {
                          let opts = {
                            UserMap: false,
                          }
                          expect(() => { morfo.setActiveOptions(opts); }).to.throw(TypeError,
                            errors.WRONG_PROPERTIES_FOR_ACTIVE_OPTS);
                        });

                        it('should set active options when opts object is provided', function() {
                          let opts = {
                            'UserMap': false,
                            'NumbersDetection': true,
                            'PunctuationDetection': true,
                            'DatesDetection': true,
                            'DictionarySearch': true,
                            'AffixAnalysis': true,
                            'CompoundAnalysis': false,
                            'RetokContractions': true,
                            'MultiwordsDetection': true,
                            'NERecognition': true,
                            'QuantitiesDetection': false,
                            'ProbabilityAssignment': true
                          }
                          let result = morfo.setActiveOptions(opts);
                          expect(result).to.be.a('undefined');
                        });

                      });
                    } catch (err) {
                      console.log(err);
                    }
                  });

                })
                done();
              })
              .catch(err => { done(new Error(err)); })
          });
        });
        done();
      })
      .catch(err => { done(new Error(err)); });
  });
});
