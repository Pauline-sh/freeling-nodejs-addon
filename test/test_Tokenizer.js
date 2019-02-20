const chai = require('chai'),
      expect = chai.expect,
      chaiAsPromised = require('chai-as-promised');

const freeling = require('../'),
      errors = require('./errors');
      Promise = require("bluebird"),
      readFile = Promise.promisify(require("fs").readFile),
      path = require('path');

const cnf="/usr/local/share/freeling/ru/tokenizer.dat";
const text="Был холодный ясный апрельский день, и часы пробили тринадцать. Уткнув подбородок в грудь, чтобы спастись от злого ветра, Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа», но все-таки впустил за собой вихрь зернистой пыли.";

chai.use(chaiAsPromised);

describe('.tokenize', function(){

    it('should be a function', function() {
      expect(freeling.tokenize).to.be.a('function');
    });

    it('promise should be rejected when parameters are invalid', function() {
      return Promise
        .all([
          expect(freeling.tokenize()).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
          expect(freeling.tokenize(cnf)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
          expect(freeling.tokenize("test")).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
          expect(freeling.tokenize(cnf,"")).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
          expect(freeling.tokenize("",text)).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
          expect(freeling.tokenize("","")).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
          expect(freeling.tokenize(1,2)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
          expect(freeling.tokenize({},1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
          expect(freeling.tokenize([],[])).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
          expect(freeling.tokenize("test",{})).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
          expect(freeling.tokenize(cnf+"test",text)).to.be.rejectedWith(TypeError, errors.WRONG_CONFIG_PATH),
      ]);
    });


    it('should reject the Promise asynchronously for invalid arguments', function(done) {
      let step=0;
      const result = freeling.tokenize("",text);
      result
        .then(()=>done(new Error('Should not have invoked the resolve handler')))
        .catch((err)=>{
          expect(err).to.be.an.instanceOf(TypeError);
          expect(err.message).to.equal(errors.NO_EMPTY_ARGUMENTS);
          expect(step).to.equal(1);
          done();
        });
      expect(step).to.equal(0);
      step++;
    });

    it('should eventually resolve the Promise', function() {
        const result = freeling.tokenize(cnf,text);
        expect(result).to.eventually.to.be.an('array');
     });


    it('should resolve the Promise asynchronously with valid parameters', function(done) {
        let step = 0;
        readFile(path.join(__dirname, 'test_text.txt'), "utf8")
           .then( data => freeling.tokenize(cnf,data))
           .then( tokens => {
                expect(tokens).to.be.an('array');
                let is_all_words=true;
                for(let token of tokens) {
                  //console.log(token.getForm());
                  if(!(token instanceof freeling.Word)) {
                    is_all_words=false;
                    return;
                  }
                }
                expect(is_all_words).to.be.true;
                done();
           })
           .catch(done);
        expect(step).to.equal(0);
        step++;
     });
});
