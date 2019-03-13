#include "word.h"
#include "sentence.h"
#include "tokenizer.h"
#include "splitter.h"
#include "analysis.h"
#include "morfo.h"
#include "hmm_tagger.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	freelingAddon::WrappedWord::Init(env, exports);
    freelingAddon::WrappedAnalysis::Init(env, exports);
    freelingAddon::WrappedSentence::Init(env, exports);
    freelingAddon::WrappedTokenizer::Init(env, exports);
    freelingAddon::WrappedMorfo::Init(env, exports);
    freelingAddon::WrappedSplitter::Init(env, exports);
    freelingAddon::WrappedHmmTagger::Init(env, exports);
    freelingAddon::InitAsyncTokenizer(env, exports);
    freelingAddon::InitAsyncSplitter(env, exports);
    freelingAddon::InitAsyncMorfo(env, exports);
    freelingAddon::InitAsyncHmmTagger(env, exports);
    return  freelingAddon::InitAsyncTokenizer(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
