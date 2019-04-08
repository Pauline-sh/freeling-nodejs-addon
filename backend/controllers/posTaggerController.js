'use strict'
const freeling=require('../../addon/freeling/freeling');
const {validationResult } = require('express-validator/check');


const getSentence=sentence=>{
    let result=[];
    let words = sentence.getSentence();
    for(let word of words) {
      let word_obj={};
      word_obj.form=word.getForm();
      word_obj.selectedAnalysis=word.getLemma();
      word_obj.selectedTag=word.getTag();
      word_obj.analysis=[];
      for(let analysis of word.getAnalysis()) {
         let a={};
         a.lemma=analysis.getLemma();
         a.tag=analysis.getTag();
         a.prob=analysis.getProb().toFixed(6);
         word_obj.analysis.push(a);
      }
     result.push(word_obj);
    }
    return result;
};

const getSentences=ls=>{
    let result=[];
    for(let sentence of ls) {
        result.push(getSentence(sentence));
    }
    return result;
};

exports.getAnalyzedSentences = async (req, res, next) => {
    try {
        console.log('analysing');
        const result = validationResult(req);
        if (result.isEmpty()) {
            let lang = 'ru',
            path = '/usr/local/share/freeling/';
            let text=`Время приближалось к одиннадцати-ноль-ноль, и в отделе документации, где работал Уинстон, сотрудники выносили стулья из кабин и расставляли в середине холла перед большим телекраном— собирались на двухминутку ненависти. Уинстон приготовился занять свое место в средних рядах, и тут неожиданно появились еще двое: лица знакомые, но разговаривать с ними ему не приходилось.`;
            let tokenizer = new freeling.Tokenizer(path+lang+'/tokenizer.dat'),
                splitter = new freeling.Splitter(path+lang + '/splitter.dat');
            let morfo = new freeling.Morfo(path, lang),
                tagger = new freeling.HmmTagger(path+lang+'/tagger.dat',true,'FORCE_TAGGER');
            let lw=await tokenizer.tokenize(text),
                ls=await splitter.split(lw);
                ls=await morfo.analyze(ls);
                ls=await tagger.analyze(ls);
                let ress=getSentences(ls);
                const fs = require('fs');
                fs.writeFile("test.json", JSON.stringify(ress), (err) => {
                    if(err) {
                        return console.log(err);
                    }

                    console.log("The file was saved!");
                });
                return res.json({ success: true, sentences:ress });
        }
        else {
            let errors=result.mapped(), error_msg='';
            for(let key in errors) error_msg+=`${errors[key].msg} `;
            throw new Error(error_msg);
        }
    }
    catch(err) {
        next(err);
    }
};
