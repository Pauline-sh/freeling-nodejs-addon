import React, { Component } from 'react';


/*function AnalyzeButton(props) {

}*/


class AnalyzeButton extends Component {
  constructor(props) {
    super(props);
  }
  render(){
    return (
      <div className="input__analyze-button__container">
        <input className="input__analyze-button" type="submit" value="Анализировать"/>
      </div>
    );
  };
};

export default AnalyzeButton;
