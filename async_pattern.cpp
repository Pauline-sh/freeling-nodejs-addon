#ifndef  ASYNC_/*name*/_H
#define  ASYNC_/*name*/_H

#include <iostream>
#include <napi.h>
#include "freeling.h"

namespace freelingAddon {
  Napi::Promise Call/*name*/Promise(const Napi::CallbackInfo& info);
  Napi::Object Init/*name*/(Napi::Env env, Napi::Object exports);

  class Async/*name*/ : public Napi::Napi::AsyncWorker {
        public:
            Async/*name*/(Napi::Function& callback, Napi::Promise::Deferred deferred);
            /*functions*/
             ~Async/*name*/();

        protected:

           virtual void Execute() override {
             try {
                /*get freeling result*/
             }
             catch(const Napi::TypeError &exc) {
                deferred.Reject(exc.Value());
             }
          }

          virtual void OnOK() override {
              Napi::HandleScope scope(Env());
              deferred.Resolve(/*get napi result*/);
              Callback().Call({});
          }

          virtual void OnError(const Napi::Error& e) override {
              Napi::HandleScope scope(Env());
              deferred.Reject(Napi::TypeError::New(Env(),"Promise can't be resolved").Value());
              Callback().Call({});
          }

        private:
            /*data*/
            Napi::Promise::Deferred deferred;
  };

};
#endif
