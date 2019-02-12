#include "analysis.h"

Napi::Object freelingAddon::GetWordAnalyses(Napi::Env env,freeling::word w) {
  Napi::Object result = Napi::Object::New(env);
  result.Set("word",Napi::String::New(env,freeling::util::wstring2string(w.get_form())));
  Napi::Array analyses =  Napi::Array::New(env);
  size_t i=0;
  for (freeling::word::iterator a=w.analysis_begin(); a!=w.analysis_end(); ++a) {
      Napi::Object analysis = Napi::Object::New(env);
      analysis.Set("lemma",Napi::String::New(env,freeling::util::wstring2string(a->get_lemma())));
      analysis.Set("pos",Napi::String::New(env,freeling::util::wstring2string(a->get_tag())));
      //std::string prob=boost::lexical_cast<std::string>(a->get_prob());
      analysis.Set("prob",Napi::Number::New(env,a->get_prob()));
      analyses.Set(i,analysis);
      i++;
  }
  result.Set("analyses",analyses);
  return result;
}

freeling::word getAnalyzedWord(std::wstring w) { //just for test
      std::wstring lang = L"ru";
      freeling::util::init_locale(L"default");
      std::wstring ipath = L"/usr/local/share/freeling/";
      std::wstring path = ipath + lang + L"/";
      freeling::maco_options opt = freelingAddon::create_maco_opt(path, lang);
      freeling::splitter sp = freelingAddon::create_splitter(path);
      freeling::tokenizer tk = freelingAddon::create_tokenizer(path);
      list<freeling::word> lw = tk.tokenize(w+L".");
      list<freeling::sentence> ls = freelingAddon::morfo_an(opt, lw, sp);
      list<freeling::sentence>::iterator is=ls.begin();
      freeling::sentence::const_iterator ww=is->begin();
      return *ww;
}

Napi::Object freelingAddon::GetAnalyses(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  try{
      //if(!info.Length()) throw Napi::TypeError::New(env, "Required parameter is not provided");
      if(info.Length()) {
        if (info[0].IsObject()) {
          Napi::Object object = info[0].As<Napi::Object>();
          WrappedWord* wrapped_word = Napi::ObjectWrap<WrappedWord>::Unwrap(object);
          Napi::String str = wrapped_word->GetForm(info).As<Napi::String>();
          std::wstring form=freeling::util::string2wstring(str.Utf8Value());
          return GetWordAnalyses(env,getAnalyzedWord(form));
       }
       else throw Napi::TypeError::New(env, "Argument must be an instance of Word");
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

Napi::Object freelingAddon::InitWordAnalyses(Napi::Env env, Napi::Object exports) {
    exports.Set("getAnalyses", Napi::Function::New(env, freelingAddon::GetAnalyses));
    return exports;
}
