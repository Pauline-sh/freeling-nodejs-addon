#ifndef ASYNC_SPLITTER_H
#define ASYNC_SPLITTER_H

#include <iostream>
#include <napi.h>

#include "freeling.h"
#include "freeling/morfo/splitter.h"

#include "addon_utils.h"
#include "word.h"
#include "sentence.h"

namespace freelingAddon {
    Napi::Promise CallAsyncSplitterPromise(const Napi::CallbackInfo& info);
    Napi::Object InitAsyncSplitter(Napi::Env env, Napi::Object exports);
    // helper function
    void CallAsyncSplitterPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred);


    class AsyncSplitter : public Napi::AsyncWorker {
    public:
        AsyncSplitter(Napi::Function& callback, Napi::Promise::Deferred deferred);
        Napi::Array getSplitSentences(Napi::Env env);
        void SetInputWordsList(const std::list<freeling::word> &input_words);
        void SetSplitter(const std::wstring &lpath);
        ~AsyncSplitter() override;

    protected:
        virtual void Execute() override {
            try {
                splitted_sentences_ = this->splitter_->split(input_words_);
            } catch(const Napi::TypeError &exc) {
                deferred.Reject(exc.Value());
            }
        }

        virtual void OnOK() override {
            Napi::HandleScope scope(Env());
            deferred.Resolve(getSplitSentences(Env()));
            Callback().Call({});
        }

        virtual void OnError(const Napi::Error& e) override {
            Napi::HandleScope scope(Env());
            deferred.Reject(Napi::TypeError::New(Env(), "Promise can't be resolved").Value());
            Callback().Call({});
        }

    private:
        freeling::splitter* splitter_;
        std::list<freeling::word> input_words_;
        std::list<freeling::sentence> splitted_sentences_;
        Napi::Promise::Deferred deferred;
    };
}

#endif // ASYNC_SPLITTER_H
