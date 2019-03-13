const freeling = require('../'),
      errors = require('./errors');

const lang = 'ru',
      path = '/usr/local/share/freeling/',
      confPath = path + lang;

const chai = require('chai'),
      expect = chai.expect,
      chaiAsPromised = require('chai-as-promised');

chai.use(chaiAsPromised);

let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
            Уткнув подбородок в грудь, чтобы спастись от злого ветра,
            Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
            но все-таки впустил за собой вихрь зернистой пыли.`;

describe('.hmmTaggerAnalyze', function() {
    let tagger = new freeling.HmmTagger(confPath+'/tagger.dat',true,1,1);
    
    it('promise should be rejected when number of parameters is wrong', function() {
          return Promise
            .all([
              expect(freeling.hmmTaggerAnalyze()).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
              expect(freeling.hmmTaggerAnalyze(tagger)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
              expect(freeling.hmmTaggerAnalyze(tagger, text, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_NUMBER),
            ]);
        });

    it('promise should be rejected when second parameter is empty', function() {
      return Promise
        .all([
          expect(freeling.hmmTaggerAnalyze(tagger, [])).to.be.rejectedWith(TypeError, errors.NO_EMPTY_ARGUMENTS),
        ]);
    });
    
     it('promise should be rejected when first parameter is not a HmmTagger instance or second is not an array', function() {
          return Promise
            .all([
              expect(freeling.hmmTaggerAnalyze({}, text)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
              expect(freeling.hmmTaggerAnalyze(tagger, 1)).to.be.rejectedWith(TypeError, errors.WRONG_ARGUMENT_TYPE),
            ]);
     });
    

    
    it('should analyze sentences', function(done) {
        this.timeout(80000);
        try {
            let tokenizer = new freeling.Tokenizer(confPath+'/tokenizer.dat');
            let splitter = new freeling.Splitter(confPath + '/splitter.dat');
            let morfo = new freeling.Morfo(path, lang);
            morfo.setActiveOptions();
            freeling.tokenize(tokenizer,text)
            .then (lw => freeling.split(splitter,lw))
            .then(ls => freeling.morfoAnalyze(morfo,ls))
            .then(ls => freeling.hmmTaggerAnalyze(tagger, ls))
            .then (analyzed_sentences=>{
               for(let sentence of analyzed_sentences) {
                    let words = sentence.getSentence();
                    for(let word of words) {
                      console.log(`selected analysis: (${word.getLemma()}, ${word.getTag()})`);
                      console.log();
                      console.log();
                    }
                  }
                done();
            })
            .catch(done);
        }
        catch(err) {
            console.log(err);
        }
    });
        
});

