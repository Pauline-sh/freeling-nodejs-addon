import React from 'react';
import AnalyzedSentence from './AnalyzedSentence';


const OutputContainer = props => {
  return (
    <div className="output-container">
      {
        props.result && props.result.map((sentence, index) => {  //sentence is an array of words
          return <AnalyzedSentence number={index+1}
                                   key={"sentence-"+index+1}
                                   sentence={sentence}
                                   option={props.option}/>
        })
      }
    </div>
  )

};

export default OutputContainer;
