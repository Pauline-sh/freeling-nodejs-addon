#include "word.h"
#include "tokenizer.h"
#include "async_splitter.h"
#include "splitter.h"
#include "analysis.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
	freelingAddon::WrappedWord::Init(env, exports);
	freelingAddon::InitAsyncAnalyses(env, exports);
    freelingAddon::WrappedSplitter::Init(env, exports);
    freelingAddon::InitAsyncSplitter(env, exports);
    return freelingAddon::InitAsyncTokenizer(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
