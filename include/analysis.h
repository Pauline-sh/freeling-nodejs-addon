#ifndef ASYNC_ANALYSIS_H
#define ASYNC_ANALYSIS_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "word.h"
#include "whole.h"
#include "addon_utils.h"


namespace freelingAddon {

  Napi::Promise CallAnalysisPromise(const Napi::CallbackInfo& info);
  Napi::Object InitAsyncAnalyses(Napi::Env env, Napi::Object exports);

  class AsyncAnalysis : public Napi::AsyncWorker {
        public:
            AsyncAnalysis(Napi::Function& callback, Napi::Promise::Deferred deferred);
            Napi::Object GetWordAnalyses(Napi::Env env);
            freeling::word getAnalyzedWord();
            void SetInputWord(std::wstring w);
             ~AsyncAnalysis();

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
