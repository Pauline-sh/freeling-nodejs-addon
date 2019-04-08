import React, { Component } from 'react';
import UniqueId from 'react-html-id';


const options = [
  "Морфологический анализ",
  "Анализ частей речи"
];

const optionsMap = {
  "Морфологический анализ": "morf",
  "Анализ частей речи": "pos-tag"
}

class AnalysisDropDownMenu extends Component {
  constructor(props) {
    super(props);
    UniqueId.enableUniqueIds(this);

    this.state = {
      opts: options,
      selectedValue: options[0]
    }

    this.props.onSelectAnalysis(optionsMap[this.state.selectedValue]);
    this.selectOption = this.selectOption.bind(this);
  }

  selectOption(event) {
    let newValue = event.target.value;
    this.setState({
      selectedValue: newValue
    }, this.props.onSelectAnalysis(optionsMap[newValue]));
  }

  render(){
    return (
      <div className="input__dropdown-menu__container">
        <select className="input__dropdown-menu" value={ this.state.selectedValue }
                onChange={ this.selectOption }>
          {
            this.state.opts.map((option, ind) => {
              return <option value={ option } key={this.nextUniqueId()}>{ option }</option>;
            })
          }
        </select>
      </div>
    );
  };
};

export default AnalysisDropDownMenu;
