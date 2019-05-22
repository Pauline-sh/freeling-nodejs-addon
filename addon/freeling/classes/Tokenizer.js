module.exports=(()=>{ 
    'use strict';
    const freeling = require('../../');
    let freeling_tokenizer=null;

    return class Tokenizer {
        constructor(cfgFile) {
            freeling_tokenizer=new freeling.Tokenizer(cfgFile);
        }
        async tokenize (text) {
            return await freeling.tokenize(freeling_tokenizer,text); 
        }
    };
})();