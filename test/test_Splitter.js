const chai = require('chai')
const freeling = require('../')
const expect = chai.expect;


describe('class Splitter', function() {
  let lang = 'ru';
  let path = '/usr/local/share/freeling/';
  describe('constructor', function() {
    it('should be a function', function() {
      expect(freeling.Splitter).to.be.a('function');
    });

    it('should throw when no arguments are provided', function() {
      expect(() => { new freeling.Splitter(); }).to.throw(TypeError,
        'Required parameter is not provided');
    });

    it('should throw when provided argument is not a string', function() {
      expect(() => { new freeling.Splitter(1); }).to.throw(TypeError,
        'Parameter should be a string');
    });

    it('should throw when config file doesn\'t exists', function() {
      expect(() => { new freeling.Splitter('somewrongpath/splitter.dat'); }).to.throw(TypeError,
        'Config file doesn\'t exist');
    });

    it('should return an instance of Splitter if config file is provided', function() {
      let testSplitter = new freeling.Splitter(path + lang + '/splitter.dat');
      expect(testSplitter).to.be.an.instanceof(freeling.Splitter);
    });

  });
});
