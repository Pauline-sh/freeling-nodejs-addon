const express = require('express');
const router = express.Router();
const posTaggerController = require('../controllers/posTaggerController');
const morfAnalyzerController = require('../controllers/morfAnalyzerController');
const textValidator = require('../validators/textValidator');

const asyncMiddleware = fn =>
  (req, res, next) => {
    Promise.resolve(fn(req, res, next))
      .catch(next);
};

router.get('/pos-tagger', asyncMiddleware(posTaggerController.getAnalyzedSentences));
router.post('/pos-tagger', textValidator.validate(),
            asyncMiddleware(posTaggerController.getAnalyzedSentences));

router.get('/morf', asyncMiddleware(morfAnalyzerController.getAnalyzedSentences));
router.post('/morf', textValidator.validate(),
            asyncMiddleware(morfAnalyzerController.getAnalyzedSentences));

module.exports = router;
