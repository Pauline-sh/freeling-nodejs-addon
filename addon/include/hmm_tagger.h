#ifndef  HMM_TAGGER_H
#define  HMM_TAGGER_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "addon_errors.h"
#include "addon_utils.h"
#include "analysis.h"

namespace freelingAddon {
    class WrappedHmmTagger : public Napi::ObjectWrap<WrappedHmmTagger> {
    public:
        static Napi::FunctionReference constructor;
        static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
        static Napi::Object Init(Napi::Env env, Napi::Object exports);
        freeling::hmm_tagger *GetInternalInstance();
        WrappedHmmTagger(const Napi::CallbackInfo &info);
        ~WrappedHmmTagger();

    private:
        void SetTagger(const Napi::CallbackInfo &info);
        freeling::hmm_tagger*tagger_;
    };

    Napi::Promise CallAsyncHmmTaggerPromise(const Napi::CallbackInfo& info);
    Napi::Object InitAsyncHmmTagger(Napi::Env env, Napi::Object exports);
    void CallAsyncHmmTaggerPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred);

    class AsyncHmmTagger : public Napi::AsyncWorker {

            public:
                AsyncHmmTagger(Napi::Function& callback, Napi::Promise::Deferred deferred);
                void SetInputSentencesList(const std::list<freeling::sentence> &input_sentences);
                void SetHmmTagger(const Napi::Env env, const Napi::Object &object_parent);

            protected:

               virtual void Execute() override {
                 try {
                        this->tagger_->analyze(input_sentences_);
                        analyzed_sentences_ = input_sentences_;
                 }
                 catch(const Napi::TypeError &exc) {
                    deferred.Reject(exc.Value());
                 }
              }

              virtual void OnOK() override {
                  Napi::HandleScope scope(Env());
                  deferred.Resolve(addonUtil::FreelingSentences2NapiArray(this->analyzed_sentences_,Env()));
                  Callback().Call({});
              }

              virtual void OnError(const Napi::Error& e) override {
                  Napi::HandleScope scope(Env());
                  deferred.Reject(Napi::TypeError::New(Env(),"Promise can't be resolved").Value());
                  Callback().Call({});
              }

            private:
                freeling::hmm_tagger*tagger_;
                std::list<freeling::sentence> input_sentences_;
                std::list<freeling::sentence> analyzed_sentences_;
                Napi::Promise::Deferred deferred;
    };
};
#endif
