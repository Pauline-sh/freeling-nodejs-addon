const chai = require('chai');
const freeling = require('../');
const errors = require('./errors');

const expect = chai.expect;


describe('class Splitter', function() {
  let lang = 'ru';
  let path = '/usr/local/share/freeling/';
  let confPath = path + lang;
  describe('constructor', function() {
    it('should be a function', function() {
      expect(freeling.Splitter).to.be.a('function');
    });

    it('should throw when no arguments are provided', function() {
      expect(() => { new freeling.Splitter(); }).to.throw(TypeError,
        errors.WRONG_ARGUMENT_NUMBER);
    });

    it('should throw when provided argument is not a string', function() {
      expect(() => { new freeling.Splitter(1); }).to.throw(TypeError,
        errors.MUST_BE_A_STRING);
    });

    it('should throw when config file doesn\'t exists', function() {
      expect(() => { new freeling.Splitter('somewrongpath/splitter.dat'); }).to.throw(TypeError,
        errors.WRONG_CONFIG_PATH);
    });

    it('should return an instance of Splitter if config file is provided', function() {
      let testSplitter = new freeling.Splitter(confPath + '/splitter.dat');
      expect(testSplitter).to.be.an.instanceof(freeling.Splitter);
    });

  });

  describe('split', function() {
    let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
                Уткнув подбородок в грудь, чтобы спастись от злого ветра,
                Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
                но все-таки впустил за собой вихрь зернистой пыли.`;

    freeling.tokenize(confPath + '/tokenizer.dat', text)
      .then( lw => {
           const sp = new freeling.Splitter(confPath + '/splitter.dat');
           let ls = sp.split(lw);

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
           //done();
      })
      .catch((err) => console.log(err));

    //const tk = new freeling.Tokenizer(confPath + '/tokenizer.dat');
    //let lw = tk.tokenize(text);

    //const sp = new freeling.Splitter(confPath + '/splitter.dat');
    //let ls = sp.split(lw);



  });

});
