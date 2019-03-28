#ifndef ASYNC_TOKENIZER_H
#define ASYNC_TOKENIZER_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "freeling/morfo/tokenizer.h"
#include "addon_utils.h"
#include "word.h"

namespace freelingAddon {
    class WrappedTokenizer : public Napi::ObjectWrap<WrappedTokenizer> {
    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        freeling::tokenizer*GetInternalInstance();
        WrappedTokenizer(const Napi::CallbackInfo &info);
        ~WrappedTokenizer();
    private:
        freeling::tokenizer*tokenizer_;
    };

    Napi::Promise CallTokenizerPromise(const Napi::CallbackInfo& info);
    Napi::Object InitAsyncTokenizer(Napi::Env env, Napi::Object exports);
    void CallAsyncTokenizerPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred);

    class AsyncTokenizer : public Napi::AsyncWorker {
            public:
                AsyncTokenizer(Napi::Function& callback, Napi::Promise::Deferred deferred);
                Napi::Array getTokens(Napi::Env env);
                void SetText(const std::wstring&input_text);
                void SetTokenizer(const Napi::Env env, const Napi::Object &object_parent);
            protected:

               virtual void Execute() override {
                 try {
                    tokens_= this->tokenizer_->tokenize(text_);
                 }
                 catch(const Napi::TypeError &exc) {
                    deferred.Reject(exc.Value());
                 }
              }

              virtual void OnOK() override {
                  Napi::HandleScope scope(Env());
                  deferred.Resolve(getTokens(Env()));
                  Callback().Call({});
              }

              virtual void OnError(const Napi::Error& e) override {
                  Napi::HandleScope scope(Env());
                  deferred.Reject(Napi::TypeError::New(Env(),"Promise can't be resolved").Value());
                  Callback().Call({});
              }

            private:
                freeling::tokenizer*tokenizer_;
                list<freeling::word> tokens_;
                std::wstring text_;
                Napi::Promise::Deferred deferred;
    };


};
#endif
