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
        Napi::Array Split();
    };
}

#endif // SPLITTER_H
