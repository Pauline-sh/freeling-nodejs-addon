import React, { Component } from 'react';
import UniqueId from 'react-html-id';


const options = [
  "Морфологический анализ",
  "Анализ частей речи"
];

class AnalysisDropDownMenu extends Component {
  constructor(props) {
    super(props);
    UniqueId.enableUniqueIds(this);

    this.state = {
      opts: options,
      selectedValue: options[0]
    }

    this.props.onSelectAnalysis(this.state.selectedValue);
    this.selectOption = this.selectOption.bind(this);
  }

  selectOption(event) {
    let newValue = event.target.value;
    this.setState({
      selectedValue: newValue
    });
    this.props.onSelectAnalysis(newValue);
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
