import React, { Component } from 'react';
import UniqueId from 'react-html-id';
import CheckBox from './CheckBox';

class OptionsContainer extends Component {
    constructor(props) {
        super(props);
        UniqueId.enableUniqueIds(this);
    }
    render(){
        return (
            <div className="options-container">
                <CheckBox key={this.nextUniqueId()} id="ner" label="Numbers Detection"/>
                <CheckBox key={this.nextUniqueId()} id="punctuation" label="Punctuation Detection"/>
                <CheckBox key={this.nextUniqueId()} id="dates" label="Dates Detection"/>
                <CheckBox key={this.nextUniqueId()} id="dict" label="Dictionary Search"/>
                <CheckBox key={this.nextUniqueId()} id="affix" label="Affix Analysis"/>
                <CheckBox key={this.nextUniqueId()} id="ner" label="NER Recognition"/>
                <CheckBox key={this.nextUniqueId()} id="quantities" label="Quantities Detection"/>
                <CheckBox key={this.nextUniqueId()} id="prob" label="Probability Assignment"/>
            </div>
        );
    };
};

export default OptionsContainer;