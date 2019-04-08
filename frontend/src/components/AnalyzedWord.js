import React from 'react';

const AnalyzedWord = props => {
    if(props.option==="morf") {
        return (
            <div className="analyzed-word">
                <h4 className="word-form">{props.word.form}</h4>
                <div className="analysis-wrapper"> {
                    props.word.analysis.map((word,index)=>{
                        return (
                            <div key={"analysis"+index+1} className="analysis">
                                <div className="word-lemma">{word.lemma}</div>
                                <div className="word-tag">{word.tag}</div>
                                <div className="word-prob">{word.prob}</div>
                            </div>
                        )
                    })
                }    
                </div>
            </div>
        )
    }
    else { //TODO
        
        return (
            <div>EMPTY</div>
        );
    }
};


export default AnalyzedWord;