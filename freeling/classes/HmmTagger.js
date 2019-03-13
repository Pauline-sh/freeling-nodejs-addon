'use strict';

const freeling = require('../../');
const force_= {
            "FORCE_NONE":0,
            "FORCE_TAGGER": 1 ,
            "FORCE_RETOK":2 
        };

let freeling_hmm_tagger;

class HmmTagger {
    
    constructor(cfgFile,rtk,force,kb=1) {
       freeling_hmm_tagger = new freeling.HmmTagger(cfgFile,rtk,force_[force],kb);
    }
    
    async analyze (sentenceList) {
        return await freeling.hmmTaggerAnalyze(freeling_hmm_tagger,sentenceList);   
    }
};

module.exports=HmmTagger;