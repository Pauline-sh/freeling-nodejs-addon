const chai = require('chai');
const expect = chai.expect;
const chaiAsPromised = require('chai-as-promised');
chai.use(chaiAsPromised);
const freeling = require('../');

async function getPromise(str) {
  let test_word = new freeling.Word(str);
  return await freeling.getAnalyses(test_word);
}

describe('.getAnalyses', function(){

    it('should be a function', function() {
      expect(freeling.getAnalyses).to.be.a('function');
    });

    it('promise should be rejected when parameters are invalid', function() {
      return Promise
        .all([
          expect(freeling.getAnalyses()).to.be.rejectedWith(TypeError, 'Required parameter is not provided'),
          expect(freeling.getAnalyses(1)).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),
          expect(freeling.getAnalyses("test")).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),
          expect(freeling.getAnalyses({})).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),
          expect(freeling.getAnalyses(true)).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),
          expect(freeling.getAnalyses(()=>{})).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),
          expect(freeling.getAnalyses([])).to.be.rejectedWith(TypeError, 'Argument must be an instance of Word'),

        ]);
    });

    it('should reject the Promise asynchronously for invalid argument', function(done) {
      this.timeout(40000);
      let step=0;
      const result = freeling.getAnalyses();
      result
        .then(()=>done(new Error('Should not have invoked the resolve handler')))
        .catch((err)=>{
          expect(err).to.be.an.instanceOf(TypeError);
          expect(err.message).to.equal('Required parameter is not provided');
          expect(step).to.equal(1);
          done();
        });
      expect(step).to.equal(0);
      step++;
    });

    it('should eventually resolve the Promise', function() {
      this.timeout(40000);
      let test_word = new freeling.Word("Смотреть");
      const result = freeling.getAnalyses(test_word);
      expect(result).to.eventually.to.be.an('object');
     });

  it('should resolve the Promise asynchronously with valid parameters', function(done) {
     this.timeout(80000);
     let step = 0;
     const promises=[getPromise("Смотреть"),getPromise("Этот")];
     Promise.all(promises)
         .then((results)=>{
            results.map( value => {
                  expect(value).to.be.an('object');
                  expect(value).to.have.property("word");
                  expect(value.word).to.be.a('string');
                  expect(value).to.have.property("analyses");
                  expect(value.analyses).to.be.an('array');
            });
            done();
         })
         .catch(done);
     expect(step).to.equal(0);
     step++;
  });

});
