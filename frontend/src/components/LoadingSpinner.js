import React from 'react';

const LoadingSpinner = props => {
  return (
    <React.Fragment>
    {
      props.loading && <div className="loader">
        <div className="line"></div>
        <div className="line"></div>
        <div className="line"></div>
        <div className="line"></div>
      </div>
    }
    </React.Fragment>
  );
};


export default LoadingSpinner;
