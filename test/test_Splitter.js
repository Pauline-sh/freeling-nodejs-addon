const { performance, PerformanceObserver } = require('perf_hooks');
const freeling = require('../'),
      errors = require('./errors'),
      Promise = require("bluebird"),
      readFile = Promise.promisify(require("fs").readFile);
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

describe('splitter', function() {
  it('should get list of words from tokenizer', function(done) {
    freeling.tokenize(confPath + '/tokenizer.dat', text)
      .then( lw => {
        describe('.split', function() {

          it('should be a function', function() {
            expect(freeling.split).to.be.a('function');
          });

          it('should return a Promise', function(done) {
            let result = freeling.split(confPath + '/splitter.dat', lw);
            expect(result).to.be.a('promise');
            result
            .then(() => { done(); })
            .catch(() => { done(); });
          });

          it('promise should be rejected when number of parameters is wrong', function() {
            return Promise
              .all([
                expect(freeling.split()).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
                expect(freeling.split(confPath)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
                expect(freeling.split(lw)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
              ]);
          });

          it('promise should be rejected when any parameter is empty', function() {
            return Promise
              .all([
                expect(freeling.split(confPath, [])).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
                expect(freeling.split("", lw)).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
                expect(freeling.split("", [])).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
              ]);
          });

          it('promise should be rejected when first parameter is not a string or second is not an array of Words', function() {
            return Promise
              .all([
                expect(freeling.split(1, 2)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
                expect(freeling.split([], lw)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
                expect(freeling.split(confPath, {})).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
              ]);
          });

          it('promise should be rejected when config path doesn\'t exist', function() {
            return Promise
              .all([
                expect(freeling.split(confPath + "test", lw)).to.be.rejectedWith(TypeError, errors.WRONG_CONFIG_PATH),
            ]);
          });

          it('should eventually resolve the Promise', function() {
            let result = freeling.split(confPath, lw);
            expect(result).to.eventually.to.be.an('array');
          });

          it('should resolve the Promise asynchronously with valid parameters', function(done) {
            let step = 0;
            let t0 = performance.now();
            freeling.split(confPath + '/splitter.dat', lw)
            .then((ls) => {
              let t1 = performance.now();
              console.log("Call to split took " + (t1 - t0) + " milliseconds.");
              describe('splitting results', function() {
                it('should return an array', function() {
                  expect(ls).to.be.an('array');
                });

                it('each element of an array should also be an array', function() {
                  let flag = true;
                  for(let sentence of ls) {
                    if(!Array.isArray(sentence)) {
                      flag = false;
                      break;
                    }
                  }
                  expect(flag).to.be.equal(true);
                });

                it('should return an array of size 2 (in case of given text)', function() {
                  expect(ls.length).to.be.equal(2);
                });
              });
              done();
            })
            .catch(() => {
              done();
            });
            expect(step).to.equal(0);
            step++;
          });
        });
        done();
      })
      .catch(err => { done(new Error(err)); });
  });
});
