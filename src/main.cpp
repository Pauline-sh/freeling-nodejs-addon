#include "word.h"
#include "tokenizer.h"
#include "analysis.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  freelingAddon::WrappedWord::Init(env, exports);
  freelingAddon::InitAsyncAnalyses(env, exports);
	return freelingAddon::InitAsyncTokenizer(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
