import React, {Component} from 'react';
import axios from 'axios';
import InputContainer from './InputContainer';
import OutputContainer from './OutputContainer';
import LoadingSpinner from './LoadingSpinner';


const ServerURL = "http://localhost:3001/";

class Container extends Component {
  constructor() {
    super();
    this.state= {
      selectedOption: "morf",
      analysisOpts: [],
      inputText: "",
      analysisResult: [],
      loading: false
    };

    this.handleFormSubmit = this.handleFormSubmit.bind(this);
  }

  handleFormSubmit(inputData) {
      this.setState({
        selectedOption: inputData.selectedOption,
        analysisOpts: inputData.analysisOpts,
        inputText: inputData.inputText,
        loading: true
      }, () => {
        let url = ServerURL;
        if (inputData.selectedOption === "pos-tag") {
          url += "pos-tagger";
        } else if (inputData.selectedOption === "morf") {
          url += "morf";
        }
        axios.post(url, {
          analysisOpts: inputData.analysisOpts,
          inputText: inputData.inputText
        })
          .then((response) => {
            this.setState({
              analysisResult: response.data.sentences,
              loading: false
            });
          })
          .catch((error) => {
            console.log(error, error.response.data.error);
            this.setState({
              loading: false
            });
            if (error.response.code === 400) {
              alert(error.response.data.error);
            }
          })
      });
    }

  render() {
        return (
        <div className="container">
            <section className="input-section">
              <LoadingSpinner loading={ this.state.loading }/>
              <InputContainer onSubmitForm={ this.handleFormSubmit }/>
            </section>
            <section className="output-section">
                <OutputContainer result={ this.state.analysisResult }
                                 option={ this.state.selectedOption }/>
            </section>
        </div>
    );
  }
};

export default Container;
