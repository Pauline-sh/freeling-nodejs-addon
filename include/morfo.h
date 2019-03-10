#ifndef MORFO_H
#define MORFO_H

#include <iostream>
#include <napi.h>

#include "freeling.h"

#include "addon_utils.h"
#include "word.h"
#include "sentence.h"


namespace freelingAddon {
    class WrappedMorfo : public Napi::ObjectWrap<WrappedMorfo> {
    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        freeling::maco *GetInternalInstance();
        WrappedMorfo(const Napi::CallbackInfo &info);
        ~WrappedMorfo();

    private:
        freeling::maco_options GetMacoOpt(Napi::Env env, const string &path_to_freeling, const string &lang);
        void SetActiveOptions(const Napi::CallbackInfo &info);
        //bool* SetActiveOptsArray(Napi::Env env, bool active_opts_arr[], const Napi::Object& active_opts_);
        freeling::maco *morfo_;
    };

    // ==== PROMISE ==== //

    Napi::Promise CallAsyncMorfoPromise(const Napi::CallbackInfo& info);
    Napi::Object InitAsyncMorfo(Napi::Env env, Napi::Object exports);
    void CallAsyncMorfoPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred);

    class AsyncMorfo : public Napi::AsyncWorker {
    public:
        AsyncMorfo(Napi::Function& callback, Napi::Promise::Deferred deferred);
        Napi::Array getAnalyzedSentences(Napi::Env env);
        void SetInputSentencesList(const std::list<freeling::sentence> &input_sentences);
        void SetMorfo(const Napi::Env env, const Napi::Object &object_parent);

    protected:
        virtual void Execute() override {
            try {
                this->morfo_->analyze(input_sentences_);
                analyzed_sentences_ = input_sentences_;
            } catch(const Napi::TypeError &exc) {
                deferred.Reject(exc.Value());
            }
        }

        virtual void OnOK() override {
            Napi::HandleScope scope(Env());
            deferred.Resolve(getAnalyzedSentences(Env()));
            Callback().Call({});
        }

        virtual void OnError(const Napi::Error& e) override {
            Napi::HandleScope scope(Env());
            deferred.Reject(Napi::TypeError::New(Env(), "Promise can't be resolved").Value());
            Callback().Call({});
        }

    private:
        freeling::maco* morfo_;
        std::list<freeling::sentence> input_sentences_;
        std::list<freeling::sentence> analyzed_sentences_;
        Napi::Promise::Deferred deferred;
    };
}

#endif // MORFO_H
