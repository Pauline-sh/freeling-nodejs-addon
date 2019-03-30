const express = require('express');
const router = express.Router();
const posTaggerController=require('../controllers/posTaggerController');
const textValidator=require('../validators/textValidator');

const asyncMiddleware = fn =>
  (req, res, next) => {
    Promise.resolve(fn(req, res, next))
      .catch(next);
};

router.get('/pos-tagger', asyncMiddleware(posTaggerController.getAnalyzedSentences));
//router.post('/pos-tagger', textValidator.validate(), posTaggerController.getAnalyzedSentences);

module.exports = router;