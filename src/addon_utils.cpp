#include "addon_utils.h"

Napi::Value EmptyCallback(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    return env.Undefined();
}
