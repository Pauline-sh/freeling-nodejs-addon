const freeling = require("./build/Release/freeling.node")

try {
	const my_word = new freeling.Word();
	console.log('Word():', JSON.stringify(my_word));

	const my_word1 = new freeling.Word('test');
	console.log('Word(string):', JSON.stringify(my_word1));	

	const my_word2 = new freeling.Word(my_word);
	console.log('Word(Word):', JSON.stringify(my_word2));

	const my_word3 = new freeling.Word('test', [my_word1, my_word2]);
	console.log('Word(string, list<Word>):', JSON.stringify(my_word3));

	console.log('is_multiword:', my_word.isMultiword());
} catch(err) {
	console.log(err.message);
}

module.exports = freeling;
