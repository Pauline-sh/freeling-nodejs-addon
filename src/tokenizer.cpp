#include "tokenizer.h"

freelingAddon::AsyncTokenizer::AsyncTokenizer(Napi::Function& callback, Napi::Promise::Deferred deferred):
                                  Napi::AsyncWorker(callback),deferred(deferred){};

void freelingAddon::AsyncTokenizer::SetText(const std::wstring&input_text) {
    text_=input_text;
}

void freelingAddon::AsyncTokenizer::SetTokenizer(const std::wstring&lpath) {
      this->tokenizer_=new freeling::tokenizer(lpath);
}

Napi::Array freelingAddon::AsyncTokenizer::getTokens(Napi::Env env){
    try {
        uint32_t i=0;
        Napi::Array tokens = Napi::Array::New(env);
        for (list<freeling::word>::const_iterator w=tokens_.begin(); w!=tokens_.end(); w++) {
             freeling::word*word_=new freeling::word(*w);
             Napi::Object value =
               freelingAddon::WrappedWord::NewInstance(env,Napi::External<freeling::word>::New(env,word_));
             tokens.Set(i,value);
             word_=NULL;
             delete word_;
             i++;
         }
         return tokens;
   }
   catch(const Napi::TypeError &exc) {
      deferred.Reject(exc.Value());
   }
   catch( ... ) {
      deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
   }
}

freelingAddon::AsyncTokenizer::~AsyncTokenizer(){
  delete tokenizer_;
};


Napi::Promise freelingAddon::CallTokenizerPromise(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  try {
      if(info.Length()) {
          if (info.Length() != 2) {
                deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
          }
          else if(info[0].IsString() && info[1].IsString()) {
                Napi::String input_path = info[0].As<Napi::String>();
                Napi::String input_text = info[1].As<Napi::String>();
                if(0 == input_path.Utf8Value().length() || 0 == input_text.Utf8Value().length()) {
                    deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
                }
                else {
                  std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
                  bool file_exist=addonUtil::file_exists(lpath);
                  if(file_exist) {
                        freeling::util::init_locale(L"default");
                        Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
                        AsyncTokenizer* worker = new AsyncTokenizer(callback, deferred);
                        worker->SetTokenizer(lpath);
                        worker->SetText(freeling::util::string2wstring(input_text.Utf8Value()));
                        worker->Queue();
                  }
                  else deferred.Reject(Napi::TypeError::New(env, WRONG_CONFIG_PATH).Value());
                }
          }

          else  deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
      }
      else deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
    }

    catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    }

    catch( ... ) {
      deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
    }

  return deferred.Promise();
}



Napi::Object freelingAddon::InitAsyncTokenizer(Napi::Env env,Napi::Object exports) {
    exports.Set("tokenize", Napi::Function::New(env, CallTokenizerPromise));
    return exports;
}
