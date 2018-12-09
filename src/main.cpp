#include "word.h"


Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return freelingAddon::Word::Init(env, exports);
}

NODE_API_MODULE(freeling, InitAll)

