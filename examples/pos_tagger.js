'use strict'

const freeling=require('../freeling/freeling');

const processSentences=ls=> {
     for(let sentence of ls) {
        let words = sentence.getSentence();
        for(let word of words) {
          console.log(`word : ${word.getForm()}, possible analysis: {`);
          let analysises = word.getAnalysis();
          for(let analysis of analysises) {
            console.log(` ( ${analysis.getLemma()}, ${analysis.getTag()} )`);
          }
          console.log(`}`);
          console.log(`selected analysis: (${word.getLemma()}, ${word.getTag()})`);
          console.log();
          console.log();
        }
      }
};

const analyze=(path,lang,text)=>{
    try {
        let tokenizer = new freeling.Tokenizer(path+lang+'/tokenizer.dat');
        let splitter = new freeling.Splitter(path+lang + '/splitter.dat');
        let morfo = new freeling.Morfo(path, lang);
        let tagger = new freeling.HmmTagger(path+lang+'/tagger.dat',true,"FORCE_TAGGER");
        morfo.setActiveOptions();
        tokenizer.tokenize(text)
        .then(lw=>splitter.split(lw))
        .then(ls=>morfo.analyze(ls))
        .then(ls=>tagger.analyze(ls))
        .then (analyzed_sentences=>processSentences(analyzed_sentences))
        .catch(err=>console.log(err));        
}
    catch(e) {
        console.log(e);
    }
    
}

const run=()=>{
    const lang = 'ru',
          path = '/usr/local/share/freeling/';
    
    let text = `Был холодный ясный апрельский день, и часы пробили тринадцать.
            Уткнув подбородок в грудь, чтобы спастись от злого ветра,
            Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа»,
            но все-таки впустил за собой вихрь зернистой пыли.`;
    
    analyze(path,lang,text);
    
}

run();
