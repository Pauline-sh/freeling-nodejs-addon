const express = require('express');
const router = express.Router();
const posTaggerController=require('../controllers/posTaggerController');
const textValidator=require('../validators/textValidator');

router.get('/pos-tagger',textValidator.validate(), posTaggerController.getAnalyzedSentences);
//router.post('/pos-tagger', textValidator.validate(), posTaggerController.getAnalyzedSentences);

module.exports = router;