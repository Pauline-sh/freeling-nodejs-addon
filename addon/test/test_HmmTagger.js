const freeling = require('../'),
      errors = require('./errors');

const cnf="/usr/local/share/freeling/ru/tagger.dat";
const chai = require('chai'),
      expect = chai.expect;

let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
            Уткнув подбородок в грудь, чтобы спастись от злого ветра,
            Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
            но все-таки впустил за собой вихрь зернистой пыли.`;

describe('HmmTagger', function() {

      it('should be a function', function() {
        expect(freeling.HmmTagger).to.be.a('function');
      });

      it('should synchronously throw error when there\'s no parameter provided', function() {
        expect(() => { new freeling.HmmTagger(); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_NUMBER);
      });

      it('should synchronously throw error when doesn\'t have 3 required parameters', function() {
        expect(() => { new freeling.HmmTagger(cnf); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_NUMBER);
        expect(() => { new freeling.HmmTagger(cnf,true); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_NUMBER);
      });


      it('should synchronously throw error when parameters are invalid', function() {
        expect(() => { new freeling.HmmTagger(1,"1",true,"1"); }).to.throw(TypeError,
          errors.WRONG_ARGUMENT_TYPE);
      });



      it('should synchronously throw error when wrong config file provided', function() {
        expect(() => { new freeling.HmmTagger("test/tokenizer.dat",true,1,1); }).to.throw(TypeError,
          errors.WRONG_CONFIG_PATH);
      });

      it('should return an instance of HmmTagger when all parameters are valid', function() {
          this.timeout(3000);
          let tagger = new freeling.HmmTagger(cnf,true,1,3);
          expect(tagger).to.be.an.instanceof(freeling.HmmTagger);
      });

    });
