#ifndef WORD_H
#define WORD_H

#include <napi.h>

#include "freeling.h"

#include "addon_utils.h"

/*
    Аннотация для знаков рядом с объявлением функции:
        '!' апи нет
        '-' апи недоделан
        '~' апи не протестирован
*/

namespace freelingAddon {
    class WrappedWord : public Napi::ObjectWrap<WrappedWord> {
    public:
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        WrappedWord(const Napi::CallbackInfo &info);


    private:
        freeling::word* GetInternalInstance();
        static Napi::FunctionReference constructor;
        void createWrappedWord1arg(const Napi::CallbackInfo &info, Napi::Env env);
        void createWrappedWord2args(const Napi::CallbackInfo &info, Napi::Env env);

        /// get word form
        Napi::Value GetForm(const Napi::CallbackInfo &info);

        /// !
        /// Get word form, lowercased.
        //const std::wstring& get_lc_form() const;

        /// !
        /// Get word phonetic form
        //const std::wstring& get_ph_form() const;

        /// !
        /// get lemma for the selected analysis in list
        //const std::wstring& get_lemma(int k=0) const;

        /// !
        /// get tag for the selected analysis
        //const std::wstring& get_tag(int k=0) const;

        /// ~
        /// true iff the word is a multiword compound
        Napi::Value IsMultiword(const Napi::CallbackInfo &info);

        freeling::word *word_;
    };
}

const std::string DEFAULT_ERR_MSG = "Something unexpected happened";

#endif // WORD_H
