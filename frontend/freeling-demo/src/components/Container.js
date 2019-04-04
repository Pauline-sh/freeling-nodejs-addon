import React, {Component} from 'react';
import InputContainer from './InputContainer';
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
            </section>
            <section className="output-section">
                <OutputContainer/>
            </section>
        </div>
    );
  }
};

export default Container;
