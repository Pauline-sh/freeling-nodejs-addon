
'use strict';

const freeling = require('../');                         
module.exports.Analysis=freeling.Analysis;
module.exports.Word=freeling.Word;
module.exports.Sentence=freeling.Sentence;
module.exports.Tokenizer=require('./classes/Tokenizer');
module.exports.Splitter=require('./classes/Splitter');
module.exports.Morfo=require('./classes/Morfo');
module.exports.HmmTagger=require('./classes/HmmTagger');
