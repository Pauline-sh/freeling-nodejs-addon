const freeling = require('../')

const tokenizer_=(()=>{
  const printTokens=(tokens)=>{
    for(let token of tokens) console.log(token.getForm());
  }
  let cnf="/usr/local/share/freeling/ru/tokenizer.dat";
  let text="Был холодный ясный апрельский день, и часы пробили тринадцать. Уткнув подбородок в грудь, чтобы спастись от злого ветра, Уинстон Смит торопливо шмыгнул за стеклянную дверь жилого дома «Победа», но все-таки впустил за собой вихрь зернистой пыли.";
  const tokenize=()=>{
      try {
        const tk = new freeling.Tokenizer(cnf);
        let tokens=tk.tokenize(text);
        return tokens;
      }
      catch(err) {
        console.log(err.message);
      }
  }
  let tokens=tokenize();
  return {
      printTokens:printTokens,
      cnf:cnf,
      text:text,
      tokens:tokens
  }

})();


module.exports.tk=tokenizer_;
