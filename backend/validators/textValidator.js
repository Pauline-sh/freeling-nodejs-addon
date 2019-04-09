const { check, validationResult } = require('express-validator/check');

exports.validate=()=>{
  return [
      check('inputText')
        .exists()
        .isString()
        .isLength({min: 1}).withMessage('Can not analyze empty text.')
        .isLength({max: 760}).withMessage('This is a demo. Only short texts are allowed.')
    ]
}
