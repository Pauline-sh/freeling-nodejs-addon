import React, { Component } from 'react';
import AnalyzedWord from './AnalyzedWord';

const AnalyzedSentence = props => {
    return (
        <div className="analyzed-sentence-wrapper">  
                <div className="analyzed-sentence">
                <header className="sentence-header">{props.number}</header> {
                        props.sentence.map((word,index)=>{ //word is an object && option can be morf or pos-tag
                            return <AnalyzedWord key={"aword"+index+1} word={word} option={props.option}/> 
                    })
                }
                </div>
        </div>
    )
};

export default AnalyzedSentence;