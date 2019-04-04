import React, { Component } from 'react';
import UniqueId from 'react-html-id';
import CheckBox from './CheckBox';

class OptionsContainer extends Component {
  constructor(props) {
    super(props);
    UniqueId.enableUniqueIds(this);
    this.state = {
      numbers: true,
      punctuation: true,
      dates: true,
      dict: true,
      affix: true,
      ner: true,
      quantities: true,
      prob: true
    }
    this.handleCheckOption = this.handleCheckOption.bind(this);
  }

  handleCheckOption(checkboxId, ifChecked) {
    this.setState({
      [checkboxId]: ifChecked
    }, () => { this.props.updateOpts(this.state) });
  }

  render(){
    return (
      <div className="options-container">
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.numbers } id="numbers" label="Numbers Detection"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.punctuation } id="punctuation" label="Punctuation Detection"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.dates } id="dates" label="Dates Detection"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.dict } id="dict" label="Dictionary Search"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.affix } id="affix" label="Affix Analysis"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.ner } id="ner" label="NER Recognition"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.quantities } id="quantities" label="Quantities Detection"/>
        <CheckBox key={this.nextUniqueId()} onCheckOption={ this.handleCheckOption }
          checked={ this.state.prob } id="prob" label="Probability Assignment"/>
      </div>
    );
  };
};

export default OptionsContainer;
