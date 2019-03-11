#ifndef SENTENCE_H
#define SENTENCE_H

#include <napi.h>
#include "freeling.h"
#include "addon_utils.h"
#include "word.h"

namespace freelingAddon {
    class WrappedSentence : public Napi::ObjectWrap<WrappedSentence> {
    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        WrappedSentence(const Napi::CallbackInfo &info);
        ~WrappedSentence();
        Napi::Value GetSentence(const Napi::CallbackInfo &info);
        static std::list<freeling::sentence> getSentencesList(Napi::Env env, Napi::Array js_arg);

    private:
        freeling::sentence* GetInternalInstance();
        freeling::sentence *sentence_;
    };
    
}

#endif
