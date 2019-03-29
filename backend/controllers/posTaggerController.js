'use strict'
const freeling=require('../addon/freeling/freeling');
const {validationResult } = require('express-validator/check');

exports.getAnalyzedSentences=(req, res, next) => {
    const result = validationResult(req);
    if (result.isEmpty()) {
        return res.json({ success: true, sentences: [] });
    }
    else {
        let errors=result.mapped(), error_msg='';
        for(let key in errors) error_msg+=`${errors[key].msg} `;
        next(new Error(error_msg)); 
    }
};