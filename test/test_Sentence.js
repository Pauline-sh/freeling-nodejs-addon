const chai = require('chai'),
      expect = chai.expect,
      chaiAsPromised = require('chai-as-promised');

const freeling = require('../'),
      errors = require('./errors');

chai.use(chaiAsPromised);
const cnf="/usr/local/share/freeling/ru/tokenizer.dat";
const text="Был холодный ясный апрельский день, и часы пробили тринадцать.";



describe('class Sentence', function() {
      describe('constructor', function() {

          it('should be a function', function() {
                expect(freeling.Sentence).to.be.a('function');
          });

          it('should throw an error when created with no parameters', function() {
              expect(() => { new freeling.Sentence(); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_NUMBER);
          });

          it('should throw an error with invalid input parameter', function() {
              expect(() => { new freeling.Sentence(1); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_TYPE);
              expect(() => { new freeling.Sentence(true); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_TYPE);
              expect(() => { new freeling.Sentence("test"); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_TYPE);
              expect(() => { new freeling.Sentence({}); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_TYPE);
              expect(() => { new freeling.Sentence(()=>{}); }).to.throw(TypeError,
                    errors.WRONG_ARGUMENT_TYPE);
              expect(() => { new freeling.Sentence([]); }).to.throw(TypeError,
                    errors.NO_EMPTY_ARGUMENTS);

          });
          
         it('should be an instance of Sentence with valid parameter', function(done) { 
             freeling.tokenize(cnf,text)
             .then(lw=>{
                  const sentence=new freeling.Sentence(lw);
                  expect(sentence).to.be.an.instanceof(freeling.Sentence);
                  done();
             })
             .catch(done)
        });
    });
    
    describe('.getSentence', function() {
         it('should be an array and each of element should be an instance of Word', function(done) { 
             freeling.tokenize(cnf,text)
             .then(lw=>{
                  const sentence=new freeling.Sentence(lw),
                        words=sentence.getSentence();
                  expect(words).to.be.an('array');
                  let is_all_words=true;
                  for(let word of words) {
                       if(!(word instanceof freeling.Word)) {
                       is_all_words=false;
                       break;
                     }
                  }
                  expect(is_all_words).to.be.true;
                  done();   
             })
            .catch(done)
        });

     });
});
