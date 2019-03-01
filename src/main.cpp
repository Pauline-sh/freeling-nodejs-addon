#include "word.h"
#include "sentence.h"
#include "tokenizer.h"
#include "splitter.h"
#include "analysis.h"
#include "pos_tagger.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	freelingAddon::WrappedWord::Init(env, exports);
    freelingAddon::WrappedAnalysis::Init(env, exports);
    freelingAddon::WrappedSentence::Init(env, exports);
    freelingAddon::InitAsyncSplitter(env, exports);
    freelingAddon::InitAsyncTokenizer(env, exports);
    return freelingAddon::InitAsyncPosTagger(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
