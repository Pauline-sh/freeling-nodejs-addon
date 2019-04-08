import React, { Component } from 'react';
import AnalyzedWord from './AnalyzedWord';
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faAngleDown } from '@fortawesome/fontawesome-free-solid';

class AnalyzedSentence extends Component {
    constructor(props) {
        super(props);
        this.state={
            height:"300px",
            iconTransform:"rotate(0deg)"
        };
        this.ChangeSize=this.ChangeSize.bind(this);
    }

    ChangeSize=()=>{
        const newHeight=this.state.height==="300px"?"auto":"300px";
        const newIconTransform=this.state.iconTransform==="rotate(0deg)"?"rotate(180deg)":"rotate(0deg)";
        this.setState({height:newHeight, iconTransform:newIconTransform});
    };

    render(){
      return (
        <div className="analyzed-sentence-wrapper">
                <div className="analyzed-sentence" style={{height:this.state.height}} onClick={this.ChangeSize}>
                    <header className="sentence-header">{this.props.number}</header>
                    {
                        this.props.sentence.map((word,index)=>{ //word is an object && option can be morf or pos-tag
                            return <AnalyzedWord key={"aword"+index+1} word={word} option={this.props.option}/>
                    })
                    }
                <FontAwesomeIcon
                icon={ faAngleDown }
                className="open-close-icon"
                style={{transform:`${this.state.iconTransform}`}}/>
                </div>
        </div>
    )

    };


};
export default AnalyzedSentence;
