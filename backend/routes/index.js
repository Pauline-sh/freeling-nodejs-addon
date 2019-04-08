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
router.post('/pos-tagger', (req, res, next) => {
  console.log(req.body);
  res.send('Got a POST to pos-tagger request')
});
//textValidator.validate(), posTaggerController.getAnalyzedSentences);
router.get('/morf', (req, res, next) => {
  res.send('Got a GET to morf request');
})
router.post('/morf', (req, res, next) => {
  console.log(req.body);
  res.send('Got a POST to morf request');
});

module.exports = router;
