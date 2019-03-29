const { check, validationResult } = require('express-validator/check');

exports.validate=()=>{
  return [
      check('text')
        .exists()
        .isString()
        .isLength({max:760})
        .withMessage('This is a demo. Only short texts are allowed.'),
    ]
}
