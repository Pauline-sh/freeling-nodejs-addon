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

    it('should resolve with valid parameter', async function() {
        this.timeout(40000);
        const test_word = new freeling.Word("Это");
        const result = await freeling.getAnalyses(test_word);
        expect(result).to.have.property("word");
        expect(result).to.have.property("analyses");
   });

   /*
   let promises=[getPromise("Смотреть"),getPromise("Этот")];
   Promise.all(promises)
       .then((results)=>{
         for(let i=0;i<results.length;i++) {
             console.log(results[i].word);
             console.log(results[i].analyses);
         }
       })
       .catch((err)=>{console.log(err);});
   */

});
