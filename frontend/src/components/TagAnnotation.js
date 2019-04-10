import React, { Component } from 'react';
import './TagAnnotation.css';


const punctuation = {
  Fd : {
    pos:'punctuation',
    type:'colon'
  },
  Fc : {
    pos:'punctuation',
    type:'comma'
  },
  Flt : {
    pos:'punctuation',
    type:'curlybracket',
    punctenclose:'close'
  },
  Fla : {
    pos:'punctuation',
    type:'curlybracket',
    punctenclose:'open'
  },
  Fs : {
    pos:'punctuation',
    type:'etc'
  },
  Fat : {
    pos:'punctuation',
    type:'exclamationmark',
    punctenclose:'close'
  },
  Faa : {
    pos:'punctuation',
    type:'exclamationmark',
    punctenclose:'open'
  },
  Fg : {
    pos:'punctuation',
    type:'hyphen'
  },
  Fz : {
    pos:'punctuation',
    type:'other'
  },
  Fpt : {
    pos:'punctuation',
    type:'parenthesis',
    punctenclose:'close'
  },
  Fpa : {
    pos:'punctuation',
    type:'parenthesis',
    punctenclose:'open'
  },
  Ft : {
    pos:'punctuation',
    type:'percentage'
  },
  Fp : {
    pos:'punctuation',
    type:'period'
  },
  Fit : {
    pos:'punctuation',
    type:'questionmark',
    punctenclose:'close'
  },
  Fia : {
    pos:'punctuation',
    type:'questionmark',
    punctenclose:'open'
  },
  Fe : {
    pos:'punctuation',
    type:'quotation'
  },
  Frc : {
    pos:'punctuation',
    type:'quotation',
    punctenclose:'close'
  },
  Fra : {
    pos:'punctuation',
    type:'quotation',
    punctenclose:'open'
  },
  Fx : {
    pos:'punctuation',
    type:'semicolon'
  },
  Fh : {
    pos:'punctuation',
    type:'slash'
  },
  Fct : {
    pos:'punctuation',
    type:'squarebracket',
    punctenclose:'close'
  },
  Fca : {
    pos:'punctuation',
    type:'squarebracket',
    punctenclose:'open'
  }
};
const pos = {
  'A':'adjective',
  'B':'preposition',
  'C':'conjunction',
  'D':'adverb',
  'E':'pronoun',
  'J':'interjection',
  'M':'compound',
  'N':'noun',
  'P':'pronominal-adv',
  'Q':'participle',
  'R':'pronominal-adj',
  'T':'particle',
  'V':'verb',
  'Y':'ordinal',
  'Z':'number',
  'W':'date',
  'I':'interjection'
};
const noun_position = ['case', 'num', 'gen', 'animate', 'form', 'degree', 'other', 'obscene'];
const noun = {
  //1
  'case': {
    'N':'nominative',
    'G':'genitive',
    'D':'dative',
    'F':'accusative',
    'C':'instrumental',
    'O':'prepositional',
    'P':'partitive',
    'L':'locative',
    'V':'vocative'
  },
  //2
  'num': {
    'S':'singular',
    'P':'plural'
  },
  //3
  'gen': {
    'M':'masculine',
    'F':'feminine',
    'N':'neuter',
    'C':'common'
  },
  //4
  'animate': {
    'A':'yes',
    'I':'no'
  },
  //5
  'form': {
    'F':'full',
    'S':'short'
  },
  //6
  'degree': {
    'E':'superlative',
    'C':'comparative',
    'P':'positive'
  },
  //7
  'other': {
    'P':'transition',
    'D':'difficult',
    'V':'corrupted',
    'R':'predicative',
    'I':'spoken',
    'A':'uncommon',
    'B':'abbreviation',
    'E':'outdated'
  },
  //8
  'obscene': {
    'H':'yes'
  }
}

class TagAnnotation extends Component {
  constructor(props) {
    super(props);
    this.state = {
      annotation: this.props.tag
    }
  }

  componentDidMount() {
    let tag = this.props.tag;
    let firstPosition = tag[0];
    // если знак пунктуации то просто возвращаем его тип
    if (punctuation.hasOwnProperty(tag)) {
      this.setState({
        annotation: punctuation[tag]['type']
      });
    // TODO:
    // в ином случае нужно узнать часть речи и вывести подробности для нее
    } else if (pos.hasOwnProperty(firstPosition)) {
      this.setState({
        annotation: pos[firstPosition]
      });
    }
  }

  render() {
    return (
      <div className="word-tag tooltip">
        { this.props.tag }
        <span className="tooltiptext">{ this.state.annotation }</span>
      </div>
    );
  }
};

export default TagAnnotation;
