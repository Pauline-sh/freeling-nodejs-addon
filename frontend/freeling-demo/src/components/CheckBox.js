import React, {Component} from 'react';

class CheckBox extends Component {

    constructor(props) {
      super(props);
      this.state={
        checked: props.checked
      };
      this.handleCheck=this.handleCheck.bind(this);
    }

    handleCheck=(e)=>{
      this.setState({checked: !this.state.checked});
      this.props.onCheckOption(e.target.id, e.target.checked);
    }

    render(){
      return(
        <div className="checkbox-wrapper">
          <label className="checkbox-label">{this.props.label}
            <input type="checkbox" id={this.props.id} onChange={this.handleCheck} defaultChecked={this.state.checked}/>
            <span className="checkmark"></span>
          </label>
        </div>
      );
    };
};


export default CheckBox;
