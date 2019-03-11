#include "tokenizer.h"


Napi::FunctionReference freelingAddon::WrappedTokenizer::constructor;

Napi::Object freelingAddon::WrappedTokenizer::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Tokenizer", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Tokenizer", func);
    return exports;
}

Napi::Object freelingAddon::WrappedTokenizer::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::Object obj = constructor.New({ arg });
    return obj;
}

freeling::tokenizer* freelingAddon::WrappedTokenizer::GetInternalInstance() {
    return this->tokenizer_;
}

freelingAddon::WrappedTokenizer::WrappedTokenizer(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedTokenizer>(info) {
        Napi::Env env=info.Env();
        Napi::HandleScope scope(env);
        try {
          if(info.Length()) {
              if(info[0].IsString()) {
                Napi::String input_path = info[0].As<Napi::String>();
                std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
                bool file_exist=addonUtil::file_exists(lpath);
                if(file_exist){
                  freeling::util::init_locale(L"default");
                  this->tokenizer_=new freeling::tokenizer(lpath);
                }
                else throw Napi::TypeError::New(env, WRONG_CONFIG_PATH);
              }
            else  throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
          }
         else throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
        }
        catch(const Napi::TypeError &exc) {
            exc.ThrowAsJavaScriptException();
        }
        catch(const std::exception &exc) {
            Napi::TypeError::New(env, exc.what()).Value();
      }
}


freelingAddon::WrappedTokenizer::~WrappedTokenizer() {
    delete this->tokenizer_;
}


freelingAddon::AsyncTokenizer::AsyncTokenizer(Napi::Function& callback, Napi::Promise::Deferred deferred):
                                  Napi::AsyncWorker(callback),deferred(deferred){};

void freelingAddon::AsyncTokenizer::SetText(const std::wstring&input_text) {
    text_=input_text;
}

void freelingAddon::AsyncTokenizer::SetTokenizer(const Napi::Env env, const Napi::Object &object_parent) {
    WrappedTokenizer* parent = Napi::ObjectWrap<freelingAddon::WrappedTokenizer>::Unwrap(object_parent);
    this->tokenizer_=parent->GetInternalInstance();
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
   catch(const std::exception &exc) {
        deferred.Reject(Napi::TypeError::New(env, exc.what()).Value());
    }
}

Napi::Promise freelingAddon::CallTokenizerPromise(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
  try {
      if (info.Length() == 2) {
          if (info[0].IsObject()&& info[0].As<Napi::Object>().InstanceOf(WrappedTokenizer::constructor.Value()) && info[1].IsString()) {
              CallAsyncTokenizerPromiseInternal(info, env, deferred);
          } else
              deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
      } else
          deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
    }

    catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    }

    catch(const std::exception &exc) {
       deferred.Reject(Napi::TypeError::New(env, exc.what()).Value());
   }

  return deferred.Promise();
}

void freelingAddon::CallAsyncTokenizerPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred) {

    Napi::String input_text = info[1].As<Napi::String>();
    if(0 == input_text.Utf8Value().length()) {
        deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
    } else {
         Napi::Object object_parent = info[0].As<Napi::Object>();
         freeling::util::init_locale(L"default");
         Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
         AsyncTokenizer* worker = new AsyncTokenizer(callback, deferred);
         worker->SetTokenizer(env,object_parent);
         worker->SetText(freeling::util::string2wstring(input_text.Utf8Value()));
         worker->Queue();
    }
    return;
}



Napi::Object freelingAddon::InitAsyncTokenizer(Napi::Env env,Napi::Object exports) {
    exports.Set("tokenize", Napi::Function::New(env, CallTokenizerPromise));
    return exports;
}
