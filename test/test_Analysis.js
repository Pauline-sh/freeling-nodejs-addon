const chai = require('chai')
const freeling = require('../')
const expect = chai.expect;

describe('getAnalyses errors', function(){

    it('should be a function', function() {
      expect(freeling.getAnalyses).to.be.a('function');
    });

    it('should throw error when parameter is not provided',
     function() {
          expect(() => { freeling.getAnalyses(); }).to.throw(TypeError,
            'Required parameter is not provided');
    });

    it("should throw error when parameter is not an instance of Word",
      function() {
           expect(() => { freeling.getAnalyses("Test"); }).to.throw(TypeError,
             'Argument must be an instance of Word');
     });
});


describe("getAnalyses result for word 'Это'", function(){
    let test_word = new freeling.Word("Это");
    let word_analyses=freeling.getAnalyses(test_word);

    it('result should be an object', ()=>expect(word_analyses).to.be.a('object'));
    it('keys should be word and analyses', ()=>{
          let obj_keys=Object.keys(word_analyses);
          expect(obj_keys[0]==='word'&&obj_keys[1]==='analyses').to.be.true;
    });

    it("word should be 'Это'", ()=>expect(word_analyses.word==='Это').to.be.true);

    it("each analysis in analyses should have lemma, pos and prob", ()=>{
          let result=true;
          for(let wa of word_analyses.analyses) {
            let wa_keys=Object.keys(wa);
            if(wa_keys[0]!='lemma' || wa_keys[1]!='pos' || wa_keys[2]!='prob') {
              result=false;
              return;
            }
          }
          expect(result).to.be.true;
    });

    let all_lemmas_str=true,all_pos_str=true,all_prop_number=true;

    for(let wa of word_analyses.analyses) {
        let wa_keys=Object.keys(wa);
        if(wa_keys[0]==='lemma'&& !(typeof wa.lemma === "string")) {
            if(all_lemmas_str) all_lemmas_str=false;
        }
        if(wa_keys[1]==='pos'&& !(typeof wa.pos === "string")) {
            if(all_pos_str) all_pos_str=false;
        }
        if(wa_keys[1]==='prob'&& isNan(wa.prob)) {
            if(all_prop_number) all_prop_number=false;
        }
    }

    it('all lemmas should be strings', ()=> expect(all_lemmas_str).to.be.true);
    it('all pos should be strings', ()=> expect(all_pos_str).to.be.true);
    it('all probs should be numbers', ()=> expect(all_prop_number).to.be.true);

  });
