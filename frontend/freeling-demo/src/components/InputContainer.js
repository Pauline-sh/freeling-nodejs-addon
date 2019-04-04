import React, { Component } from 'react';
import AnalysisDropDownMenu from './AnalysisDropDownMenu';
import AnalyzeButton from './AnalyzeButton';
import OptionsContainer from './OptionsContainer';
import './InputContainer.css';


class InputContainer extends Component {
  constructor(props) {
    super(props);

    this.state = {
      analysisSelect: null,
      analysisOpts: []
    }

    this.handleSelectAnalysis = this.handleSelectAnalysis.bind(this);
    this.handleOptsUpdate = this.handleOptsUpdate.bind(this);
    this.submitInputText = this.submitInputText.bind(this);
  }

  handleSelectAnalysis(option) {
    this.setState({
      analysisSelect: option
    });
  }

  handleOptsUpdate(opts) {
    this.setState({
      analysisOpts: opts
    });
  }

  submitInputText(event) {
    event.preventDefault();
    console.log(this.state.analysisSelect);
    console.log(this.state.analysisOpts);
  }

  render() {
    return (
    <React.Fragment>
      <form className="input-container" onSubmit={ this.submitInputText }>
        <div className="input-container__left">
          <textarea id="input__textarea" autoFocus placeholder="Введите текст для анализа..."></textarea>
          <div className="input__controllers">
            <AnalysisDropDownMenu onSelectAnalysis={ this.handleSelectAnalysis }/>
            <AnalyzeButton/>
          </div>
        </div>
        <OptionsContainer updateOpts={ this.handleOptsUpdate }/>
      </form>
    </React.Fragment>
    );
  };
};

export default InputContainer;
