#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "word.h"
#include "addon_utils.h"

namespace freelingAddon {

    class WrappedAnalysis : public Napi::ObjectWrap<WrappedAnalysis> {

    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        WrappedAnalysis(const Napi::CallbackInfo &info);
        Napi::Value HasProb(const Napi::CallbackInfo &info);
        Napi::Value HasDistance(const Napi::CallbackInfo &info);
        Napi::Value GetLemma(const Napi::CallbackInfo &info);
        Napi::Value GetTag(const Napi::CallbackInfo &info);
        Napi::Value GetProb(const Napi::CallbackInfo &info);
        Napi::Value GetDistance(const Napi::CallbackInfo &info);
        Napi::Value IsRetokenizable(const Napi::CallbackInfo &info);
        Napi::Value GetRetokenizable(const Napi::CallbackInfo &info);

    private:
        freeling::analysis* GetInternalInstance();
        freeling::analysis*analysis_;
    };
};

#endif
