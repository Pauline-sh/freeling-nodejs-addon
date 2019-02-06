#include "word.h"
#include "tokenizer.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  freelingAddon::WrappedWord::Init(env, exports);
	return freelingAddon::WrappedTokenizer::Init(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
