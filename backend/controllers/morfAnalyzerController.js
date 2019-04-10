'use strict'
const freeling=require('../../addon/freeling/freeling');
const { validationResult } = require('express-validator/check');
const getSentences = require('../utils/getSentences');

exports.getAnalyzedSentences = async (req, res, next) => {
  try {
    const result = validationResult(req);
    console.log(req.body);
    if (result.isEmpty()) {
      const lang = 'ru',
            path = '/usr/local/share/freeling/',
            text = req.body.inputText;

      console.log('creating tokenizer and splitter...');
      let tokenizer = new freeling.Tokenizer(path + lang + '/tokenizer.dat'),
          splitter = new freeling.Splitter(path + lang + '/splitter.dat');

      console.log('creating morfo...');
      let morfo = new freeling.Morfo(path, lang);
      morfo.setActiveOptions(req.analysisOpts);

      console.log('analysing...');
      let lw = await tokenizer.tokenize(text);
      let ls = await splitter.split(lw);
      ls = await morfo.analyze(ls);
      let result = getSentences.getSentences(ls);
        
      return res.json({
                        success: true,
                        sentences:result
                      });
    } else {
      let errors = result.mapped(),
          error_msg = '';
      for(let key in errors)
        error_msg += `${errors[key].msg} `;
      throw new Error(error_msg);
    }
  }
  catch(err) {
    next(err);
  }
};
