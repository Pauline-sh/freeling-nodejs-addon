'use strict';

const freeling = require('../../');
let freeling_morfo;

class Morfo {
    
    constructor(path,lang) {
       freeling_morfo = new freeling.Morfo(path, lang);
    }
    
    setActiveOptions (opts) {
           if (opts) freeling_morfo.setActiveOptions(opts);
           else freeling_morfo.setActiveOptions();
    }
    
    async analyze (sentenceList) {
        return await freeling.morfoAnalyze(freeling_morfo,sentenceList);   
    }
};

module.exports=Morfo;