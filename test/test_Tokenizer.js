const chai = require('chai')
const freeling = require('../')
const expect = chai.expect;

describe('class Tokenizer', function() {

      describe('constructor', function() {
        it('should be a function', function() {
          expect(freeling.Tokenizer).to.be.a('function');
        });

        it('should throw error when path to config file is not provided',
         function() {
              expect(() => { new freeling.Tokenizer(); }).to.throw(TypeError,
                'Required parameter is not provided');
        });

        it("should throw error when path to config file doesn't exist ",
         function() {
              expect(() => { new freeling.Tokenizer("/freeling/tokenizer.dat"); }).to.throw(TypeError,
                "Config file doesn't exist");
        });

        it("should throw error when passed parameter is not a string",
         function() {
              expect(() => { new freeling.Tokenizer(0); }).to.throw(TypeError,
                "Invalid parameter");
        });
    });

    describe('run_Tokenizer', function() {
        const tk= require('./run_Tokenizer').tk;
          it("function 'tokenize' should return an array", function() {
            expect(tk.tokens).to.be.a('array');
          });

          it("each token  should be instance of class Word", function() {
              let result=true;
              for(let token of tk.tokens) {
                if(!(token instanceof freeling.Word)) {
                  result=false;
                  return;
                }
              }
              expect(result).to.be.true;
          });

      });
  });
