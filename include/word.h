#ifndef WORD_H
#define WORD_H

#include <napi.h>
#include "freeling.h"
#include "addon_utils.h"


namespace freelingAddon {
    class WrappedWord : public Napi::ObjectWrap<WrappedWord> {
    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);

        WrappedWord(const Napi::CallbackInfo &info);

        static std::list<freeling::word> getWordsList(Napi::Env env, Napi::Array js_arg);

        /// get word form
        Napi::Value GetForm(const Napi::CallbackInfo &info);

        /// Get word form, lowercased.
        Napi::Value GetLcForm(const Napi::CallbackInfo &info);

        /// Get word phonetic form
        Napi::Value GetPhForm(const Napi::CallbackInfo &info);

        /// get lemma for the selected analysis in list
        Napi::Value GetLemma(const Napi::CallbackInfo &info);

        /// get tag for the selected analysis
        Napi::Value GetTag(const Napi::CallbackInfo &info);

        /// true iff the word is a multiword compound
        Napi::Value IsMultiword(const Napi::CallbackInfo &info);

    private:
        freeling::word* GetInternalInstance();
        void createWrappedWord1arg(const Napi::CallbackInfo &info, Napi::Env env);
        void createWrappedWord2args(const Napi::CallbackInfo &info, Napi::Env env);
        freeling::word *word_;
    };
}

#endif // WORD_H
