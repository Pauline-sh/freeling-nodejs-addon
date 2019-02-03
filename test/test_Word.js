const chai = require('chai')
const freeling = require('../')

const expect = chai.expect;


describe('freeling-addon', function() {

  it('should have all expected keys', function() {
    expect(freeling).to.contain.all.keys(['Word']);
  });

  describe('class Word', function() {
    describe('constructor', function() {

      it('should be a function', function() {
        expect(freeling.Word).to.be.a('function');
      });

      it('should synchronously throw when more than 3 parameters', function() {
        expect(() => { new freeling.Word(1, 2, 3, 4); }).to.throw(TypeError,
          'The maximum possible number of arguments is 3');
      });

      it('should synchronously throw when first parameter is not a string or second is not an array', function() {
        expect(() => { new freeling.Word(1, []); }).to.throw(TypeError,
          'The first argument must be a string and the second must be an array of Words');
        expect(() => { new freeling.Word("test", "not an array"); }).to.throw(TypeError,
          'The first argument must be a string and the second must be an array of Words');
        expect(() => { new freeling.Word(1, "not an array"); }).to.throw(TypeError,
          'The first argument must be a string and the second must be an array of Words');
      });

    });
  });

});
