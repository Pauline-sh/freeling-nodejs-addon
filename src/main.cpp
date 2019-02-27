#include "word.h"
#include "sentence.h"
#include "tokenizer.h"
#include "splitter.h"
#include "analysis.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	freelingAddon::WrappedWord::Init(env, exports);
    freelingAddon::WrappedSentence::Init(env, exports);
    freelingAddon::InitAsyncAnalyses(env, exports);
    freelingAddon::InitAsyncSplitter(env, exports);
    return freelingAddon::InitAsyncTokenizer(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
