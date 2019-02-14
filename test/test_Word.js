const chai = require('chai')
const freeling = require('../')

const expect = chai.expect;
const testString = 'test';

/*
describe('freeling-addon', function() {

  it('should have all expected keys', function() {
    expect(freeling).to.contain.all.keys(['Word','Tokenizer']);
  });
*/
describe('class Word', function() {
  describe('constructor', function() {

    it('should be a function', function() {
      expect(freeling.Word).to.be.a('function');
    });

    it('should synchronously throw when more than 3 parameters', function() {
      expect(() => { new freeling.Word(1, 2, 3, 4); }).to.throw(TypeError,
        'The maximum possible number of arguments is 3');
    });

    it('should return an instance of Word when created with no parameters', function() {
      let testWord = new freeling.Word();
      expect(testWord).to.be.an.instanceof(freeling.Word);
    });

    it('should synchronously throw when parameter is not a string or an instance of Word', function() {
      expect(() => { new freeling.Word([]); }).to.throw(TypeError,
        'Invalid argument');
    });

    it('should return an instance of Word when the first argument is a string', function() {
      let firstTestWord = new freeling.Word(testString);
      expect(firstTestWord).to.be.an.instanceof(freeling.Word);
      expect(firstTestWord.getForm()).to.equal(testString);
    });

    it('should return an instance of Word when the first argument is an instance of Word', function() {
        let firstTestWord = new freeling.Word(testString);
        let secondTestWord = new freeling.Word(firstTestWord);
        expect(secondTestWord).to.be.an.instanceof(freeling.Word);
        expect(secondTestWord.getForm()).to.equal(firstTestWord.getForm());
    });

    it('should return an instance of Word when the first argument is a string and the second is an array of Words', function() {
        let firstTestWord = new freeling.Word(testString);
        let secondTestWord = new freeling.Word(testString, [firstTestWord]);
        expect(secondTestWord).to.be.an.instanceof(freeling.Word);
        // expect(secondTestWord.getForm()).to.equal(firstTestWord.getForm());
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

  describe('getForm()', function() {
    it('should return a form of word', function() {
        let myWord = new freeling.Word(testString);
        expect(myWord.getForm()).to.equal(testString);
    });
  });

  describe('getLcForm()', function() {
    it('should return a form of word', function() {
        let myWord = new freeling.Word(testString.toUpperCase());
        expect(myWord.getLcForm()).to.equal(testString);
    });
  });

  describe('getPhForm()', function() {

  });

  describe('getLemma()', function() {

  });

  describe('getTag()', function() {

  });

  describe('isMultiword()', function() {

  });

});

//});
