#include "word.h"
#include "sentence.h"
#include "tokenizer.h"
#include "splitter.h"
#include "analysis.h"
#include "morfo.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	freelingAddon::WrappedWord::Init(env, exports);
    freelingAddon::WrappedAnalysis::Init(env, exports);
    freelingAddon::WrappedSentence::Init(env, exports);
    freelingAddon::WrappedTokenizer::Init(env, exports);
    freelingAddon::WrappedMorfo::Init(env, exports);
    freelingAddon::InitAsyncSplitter(env, exports);
    freelingAddon::InitAsyncTokenizer(env, exports);
    freelingAddon::InitAsyncMorfo(env, exports);
    return  freelingAddon::InitAsyncTokenizer(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
