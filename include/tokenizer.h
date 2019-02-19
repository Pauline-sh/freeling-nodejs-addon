#ifndef ASYNC_TOKENIZER_H
#define ASYNC_TOKENIZER_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "freeling/morfo/tokenizer.h"
#include "addon_utils.h"
#include "word.h"

namespace freelingAddon {

  Napi::Promise CallTokenizerPromise(const Napi::CallbackInfo& info);
  Napi::Object InitAsyncTokenizer(Napi::Env env, Napi::Object exports);

  class AsyncTokenizer : public Napi::AsyncWorker {
        public:
            AsyncTokenizer(Napi::Function& callback, Napi::Promise::Deferred deferred);
            Napi::Array getTokens(Napi::Env env);
            void SetText(const std::wstring&input_text);
            void SetTokenizer(const std::wstring&lpath);
            ~AsyncTokenizer();

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
