#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "word.h"
#include "whole.h"

namespace freelingAddon {

  Napi::Value EmptyCallback(const Napi::CallbackInfo& info);
  Napi::Promise CallPromise(const Napi::CallbackInfo& info);
  Napi::Object InitWordAnalyses(Napi::Env env, Napi::Object exports);

  class Analysis : public Napi::AsyncWorker {
        public:
            Analysis(Napi::Function& callback, Napi::Promise::Deferred deferred);
            Napi::Object GetWordAnalyses(Napi::Env env);
            freeling::word getAnalyzedWord();
            void SetInputWord(std::wstring w);
             ~Analysis();

        protected:

           virtual void Execute() override {
             try {
                analyzed_word=getAnalyzedWord();
             }
             catch(const Napi::TypeError &exc) {
                deferred.Reject(exc.Value());
             }
          }

          virtual void OnOK() override {
              Napi::HandleScope scope(Env());
              deferred.Resolve(GetWordAnalyses(Env()));
              Callback().Call({});
          }

          virtual void OnError(const Napi::Error& e) override {
              Napi::HandleScope scope(Env());
              deferred.Reject(Napi::TypeError::New(Env(), "Promise can't be resolved").Value());
              Callback().Call({});
          }

        private:
            freeling::word analyzed_word;
            std::wstring input_word;
            Napi::Promise::Deferred deferred;
  };

};
#endif
