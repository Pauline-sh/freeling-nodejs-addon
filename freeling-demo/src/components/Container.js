import React from 'react';
import InputContainer from './InputContainer';
import OptionsContainer from './OptionsContainer';
import OutputContainer from './OutputContainer';

const  Container = () => {
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
};

export default Container;
