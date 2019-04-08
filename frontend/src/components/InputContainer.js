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
      analysisOpts: [],
      inputText: "",
      inputPlaceholderInitial: "Введите текст для анализа (до 760 знаков)",
      inputPlaceholderErrMsg: "Необходимо ввести текст!",
      borderColorInitial: "burlywood",
      borderColorErrMsg: "red"
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
    let textArea = document.getElementById("input__textarea");
    let text = textArea.value;
    /*if (!text) {
      textArea.placeholder = this.state.inputPlaceholderErrMsg;
      textArea.style = "border-color: " + this.state.borderColorErrMsg;
    } else {*/
      textArea.placeholder = this.state.inputPlaceholderInitial;
      textArea.style = "border-color: " + this.state.borderColorInitial;

      this.setState({
        inputText: text
      }, () => {
        this.props.onSubmitForm({"selectedOption": this.state.analysisSelect,
                                 "analysisOpts": this.state.analysisOpts,
                                 "inputText": this.state.inputText})
        });
    //}
  }

  render() {
    return (
    <React.Fragment>
      <form className="input-container" onSubmit={ this.submitInputText }>
        <div className="input-container__left">
          <textarea id="input__textarea" autoFocus placeholder={ this.state.inputPlaceholderInitial }></textarea>
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
