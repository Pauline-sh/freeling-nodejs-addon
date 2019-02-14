#include "word.h"
#include "tokenizer.h"
#include "splitter.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    freelingAddon::WrappedWord::Init(env, exports);
    freelingAddon::WrappedSplitter::Init(env, exports);
    return freelingAddon::WrappedTokenizer::Init(env, exports);
}

NODE_API_MODULE(freeling, InitAll)
