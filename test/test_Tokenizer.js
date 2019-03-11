const freeling = require('../'),
      errors = require('./errors');

const cnf="/usr/local/share/freeling/ru/tokenizer.dat";

const chai = require('chai'),
      expect = chai.expect,
      Promise = require("bluebird"),
      readFile = Promise.promisify(require("fs").readFile),
      path = require('path'),
      chaiAsPromised = require('chai-as-promised');

chai.use(chaiAsPromised);


let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
            Уткнув подбородок в грудь, чтобы спастись от злого ветра,
            Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
            но все-таки впустил за собой вихрь зернистой пыли.`;

describe('Tokenizer', function() {

      it('should be a function', function() {
        expect(freeling.Tokenizer).to.be.a('function');
      });

      it('should synchronously throw error when there\'s no parameter provided', function() {
        expect(() => { new freeling.Tokenizer(); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_NUMBER);
      });

      it('should synchronously throw error when parameter is not a string', function() {
        expect(() => { new freeling.Tokenizer(1); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_TYPE);
      });
     
      it('should synchronously throw error when wrong config file provided', function() {
        expect(() => { new freeling.Tokenizer("test/tokenizer.dat"); }).to.throw(TypeError,
          errors.WRONG_CONFIG_PATH);
      });

      it('should return an instance of Tokenizer when the argument is string', function() {
          let tokenizer = new freeling.Tokenizer(cnf);
          expect(tokenizer).to.be.an.instanceof(freeling.Tokenizer);
      });

    });


describe('.tokenize', function() {
    let tokenizer = new freeling.Tokenizer(cnf);
    
    it('promise should be rejected when number of parameters is wrong', function() {
          return Promise
            .all([
              expect(freeling.tokenize()).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
              expect(freeling.tokenize(tokenizer)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
              expect(freeling.tokenize(tokenizer, text, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
            ]);
        });

    it('promise should be rejected when second parameter is empty', function() {
      return Promise
        .all([
          expect(freeling.tokenize(tokenizer, "")).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
        ]);
    });
    
     it('promise should be rejected when first parameter is not a Tokenizer instance or second is not a string', function() {
          return Promise
            .all([
              expect(freeling.tokenize({}, text)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
              expect(freeling.tokenize(tokenizer, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
            ]);
     });
    
     it('should tokenize data', function(done) {
        readFile(path.join(__dirname, 'test_text.txt'), "utf8")
           .then( data => freeling.tokenize(tokenizer,data))
           .then( tokens => {
                expect(tokens).to.be.an('array');
                let is_all_words=true;
                for(let token of tokens) {
                if(!(token instanceof freeling.Word)) {
                    is_all_words=false;
                    return;
                  }
                }
                expect(is_all_words).to.be.true;
                done();
           })
           .catch(done);
        });
});