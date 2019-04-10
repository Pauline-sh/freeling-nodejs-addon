import React from 'react';
import TagAnnotation from './TagAnnotation';


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
                <TagAnnotation tag={word.tag}/>
                <div className="word-prob">{word.prob}</div>
              </div>
            )
          })
        }
        </div>
      </div>
    )
  }
  else if (props.option==="pos-tag") {
    return (
      <div className="analyzed-word">
        <h4 className="word-form">{ props.word.form }</h4>
        <div className="analysis-wrapper">
          <div className="analysis">
            <div className="word-lemma">{ props.word.selectedAnalysis }</div>
            <TagAnnotation tag={ props.word.selectedTag }/>
          </div>
        </div>
      </div>
    );
  }
};


export default AnalyzedWord;
