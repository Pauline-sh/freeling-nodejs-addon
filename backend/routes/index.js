const express = require('express');
const router = express.Router();
const posTagger=require('../controllers/posTagger');

router.get('/pos-tagger', posTagger.getAnalyzedSentences);

module.exports = router;