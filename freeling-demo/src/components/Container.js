import React, {Component} from 'react';
import InputContainer from './InputContainer';
import OptionsContainer from './OptionsContainer';
import OutputContainer from './OutputContainer';

class  Container extends Component {
    constructor() {
        super();
        this.state= {
            selectedOptions:{}
        };
    }
    
    render() {
        return (
        <div className="container">
            <section className="input-section">
                <InputContainer/>
                <OptionsContainer/>
            </section>
            <section className="output-section">
                <OutputContainer/>
            </section>
        </div>
    );
  }
};

export default Container;
