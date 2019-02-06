#include "tokenizer.h"

Napi::FunctionReference freelingAddon::WrappedTokenizer::constructor;

Napi::Object freelingAddon::WrappedTokenizer::Init(Napi::Env env,Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func=DefineClass(env,"Tokenizer", {
      InstanceMethod("tokenize",&WrappedTokenizer::Tokenize)
  });
  constructor=Napi::Persistent(func);
  constructor.SuppressDestruct();
  exports.Set("Tokenizer", func);
  return exports;
}

freeling::tokenizer* freelingAddon::WrappedTokenizer::GetInternalInstance() {
    return this->tokenizer_;
}

freelingAddon::WrappedTokenizer::WrappedTokenizer(const Napi::CallbackInfo&info):Napi::ObjectWrap<WrappedTokenizer>(info) {
    Napi::Env env=info.Env();
    Napi::HandleScope scope(env);
    try {
      if(info.Length()) {
          if(info[0].IsString()) {
            Napi::String input_path = info[0].As<Napi::String>();
            std::wstring lpath = convert_string_to_wstring(input_path);
            bool file_exist=file_exists(lpath);
            if(file_exist){
              freeling::util::init_locale(L"default");
              this->tokenizer_=new freeling::tokenizer(lpath);
            }
            else throw Napi::TypeError::New(env, "Config file doesn't exist");
          }
        else  throw Napi::TypeError::New(env, "Invalid parameter");
      }
     else throw Napi::TypeError::New(env, "Required parameter is not provided");
    }
    catch(const Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    }
    catch( ... ) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

Napi::Array freelingAddon::WrappedTokenizer::getTokens(Napi::Env env,const std::wstring&text){
    try {
        list<freeling::word> lw = this->tokenizer_->tokenize(text);
        std::size_t i=0;
        Napi::Array tokens = Napi::Array::New(env);
        for (list<freeling::word>::const_iterator w=lw.begin(); w!=lw.end(); w++) {
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
      exc.ThrowAsJavaScriptException();
   }
   catch( ... ) {
       Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
   }
}

Napi::Value freelingAddon::WrappedTokenizer::Tokenize(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if(info.Length()) {
          if(info[0].IsString()) {
            Napi::String input_text = info[0].As<Napi::String>();
            std::wstring text=convert_string_to_wstring(input_text);
            return getTokens(env,text);
          }
          else  throw Napi::TypeError::New(env, "Invalid parameter");
        }
        else throw Napi::TypeError::New(env, "Required parameter is not provided");
    }
    catch(const Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    }
    catch( ... ) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}
