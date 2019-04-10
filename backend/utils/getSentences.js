const getSentence = sentence => {
  let result = [];
  let words = sentence.getSentence();
  for(let word of words) {
    let word_obj = {};
    word_obj.form = word.getForm();
    word_obj.selectedAnalysis = word.getLemma();
    word_obj.selectedTag = word.getTag();
    word_obj.analysis = [];
    for(let analysis of word.getAnalysis()) {
      let a = {};
      a.lemma = analysis.getLemma();
      a.tag = analysis.getTag();
      a.prob = analysis.getProb().toFixed(6);
      word_obj.analysis.push(a);
    }
    result.push(word_obj);
  }
  return result;
};

exports.getSentences = ls => {
  let result = [];
  for(let sentence of ls) {
    result.push(getSentence(sentence));
  }
  return result;
};