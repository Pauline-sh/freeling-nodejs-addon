#ifndef WORD_H
#define WORD_H

#include <napi.h>

#include "freeling.h"
#include "stringconvert.h"

namespace freelingAddon {
    class Word : public Napi::ObjectWrap<Word> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        Word(const Napi::CallbackInfo& info);

    private:
        freeling::word* GetInternalInstance();

        /// constructor
        /*  word();
            word(const std::wstring &);
            word(const std::wstring &, const std::list<word> &);
            word(const std::wstring &, const std::list<analysis> &, const std::list<word> &);
            word(const word &); */
        static Napi::FunctionReference constructor;

        /// true iff the word is a multiword compound
        // bool is_multiword() const;
        Napi::Value IsMultiword(const Napi::CallbackInfo& info);

        freeling::word *word_;
    };
}

#endif // WORD_H
