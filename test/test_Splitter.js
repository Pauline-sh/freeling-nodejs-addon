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
  it('should get list of words from tokenizer', function(done) {
    freeling.tokenize(confPath + '/tokenizer.dat', text)
      .then( lw => {
        describe('Splitter', function() {

          it('should be a function', function() {
            expect(freeling.Splitter).to.be.a('function');
          });

          it('should synchronously throw when doesn\'t have 1 parameter', function() {
            expect(() => { new freeling.Splitter(); }).to.throw(TypeError,
              errors.WRONG_ARGUMENT_NUMBER);
            expect(() => { new freeling.Splitter('somepath', 'someotherstring'); }).to.throw(TypeError,
              errors.WRONG_ARGUMENT_NUMBER);
          });

          it('should synchronously throw when parameter is not a string', function() {
            expect(() => { new freeling.Splitter(1); }).to.throw(TypeError,
              errors.WRONG_ARGUMENT_TYPE);
          });

          it('should synchronously throw when config path doesn\'t exist', function() {
              expect(() => { new freeling.Splitter(confPath + 'test'); }).to.throw(TypeError,
                errors.WRONG_CONFIG_PATH);
          });

          it('should return an instance of Splitter when the path in argument is correct', function() {
              let splitter = new freeling.Splitter(confPath + '/splitter.dat');
              expect(splitter).to.be.an.instanceof(freeling.Splitter);
          });
        });
        done();
      })
      .catch(err => { done(new Error(err)); });
  });
});
