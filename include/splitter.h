#ifndef SPLITTER_H
#define SPLITTER_H

#include <iostream>
#include <napi.h>

#include "freeling.h"
#include "freeling/morfo/splitter.h"

#include "addon_utils.h"
#include "word.h"

namespace freelingAddon {
    class WrappedSplitter : public Napi::ObjectWrap<WrappedSplitter> {
    public:
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        WrappedSplitter(const Napi::CallbackInfo &info);

    private:
        static Napi::FunctionReference constructor;
        freeling::splitter* splitter_;
        freeling::splitter* getInternalInstance();

        Napi::Array getSplitSentences(Napi::Env env, std::list<freeling::word> words);
        Napi::Value Split(const Napi::CallbackInfo &info);

        //Napi::Value OpenSession(const Napi::CallbackInfo &info);
        //void CloseSession(const Napi::CallbackInfo &info);

        //std::list<sentence> split(session_id ses, const std::list<word> &ls, bool flush) const;
    };
}

#endif // SPLITTER_H