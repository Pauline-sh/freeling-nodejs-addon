'use strict';

const freeling = require('../../');
let freeling_splitter;

class Splitter {
    constructor(cfgFile) {
       freeling_splitter=new freeling.Splitter(cfgFile);
    }
    async split (wordList) {
        return await freeling.split(freeling_splitter,wordList);   
    }
};

module.exports=Splitter;