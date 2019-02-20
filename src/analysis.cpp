#include "analysis.h"

freelingAddon::AsyncAnalysis::AsyncAnalysis(Napi::Function& callback, Napi::Promise::Deferred deferred):
                                  Napi::AsyncWorker(callback),deferred(deferred){};

void freelingAddon::AsyncAnalysis::SetInputWord(std::wstring w) {
    input_word=w;
}


freeling::word freelingAddon::AsyncAnalysis::getAnalyzedWord() {
      std::wstring lang = L"ru";
      freeling::util::init_locale(L"default");
      std::wstring ipath = L"/usr/local/share/freeling/";
      std::wstring path = ipath + lang + L"/";
      freeling::maco_options opt = addonUtil::create_maco_opt(path, lang);
      freeling::splitter sp = addonUtil::create_splitter(path);
      freeling::tokenizer tk = addonUtil::create_tokenizer(path);
      list<freeling::word> lw = tk.tokenize(input_word+L".");
      list<freeling::sentence> ls = addonUtil::morfo_an(opt, lw, sp);
      list<freeling::sentence>::iterator is=ls.begin();
      freeling::sentence::const_iterator ww=is->begin();
      return *ww;
}

Napi::Object freelingAddon::AsyncAnalysis::GetWordAnalyses(Napi::Env env) {
      Napi::Object result = Napi::Object::New(env);
      result.Set("word",Napi::String::New(env,freeling::util::wstring2string(analyzed_word.get_form())));
      Napi::Array analyses =  Napi::Array::New(env);
      size_t i=0;
      for (freeling::word::iterator a=analyzed_word.analysis_begin(); a!=analyzed_word.analysis_end(); ++a) {
          Napi::Object analysis = Napi::Object::New(env);
          analysis.Set("lemma",Napi::String::New(env,freeling::util::wstring2string(a->get_lemma())));
          analysis.Set("pos",Napi::String::New(env,freeling::util::wstring2string(a->get_tag())));
          analysis.Set("prob",Napi::Number::New(env,a->get_prob()));
          analyses.Set(i,analysis);
          i++;
      }
      result.Set("analyses",analyses);
      return result;
}

freelingAddon::AsyncAnalysis::~AsyncAnalysis(){};

Napi::Promise freelingAddon::CallAnalysisPromise(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    try{
        if(info.Length()) {
          if (info[0].IsObject() && info[0].As<Napi::Object>().InstanceOf(WrappedWord::constructor.Value())) {
              Napi::Object object = info[0].As<Napi::Object>();
              WrappedWord* wrapped_word = Napi::ObjectWrap<WrappedWord>::Unwrap(object);
              Napi::String str = wrapped_word->GetForm(info).As<Napi::String>();
              std::wstring form=freeling::util::string2wstring(str.Utf8Value());
              Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
              AsyncAnalysis* worker = new AsyncAnalysis(callback, deferred);
              worker->SetInputWord(form);
              worker->Queue();
         }
         else {
           deferred.Reject(Napi::TypeError::New(env, MUST_BE_AN_INSTANCE_OF_WORD).Value());
         }
       }
       else {
          deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
       }
    }
    catch(const Napi::TypeError &exc) {
       deferred.Reject(exc.Value());
    }
    catch( ... ) {
        deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
    }
    return deferred.Promise();
}

Napi::Object freelingAddon::InitAsyncAnalyses(Napi::Env env, Napi::Object exports) {
    exports.Set("getAnalyses", Napi::Function::New(env, CallAnalysisPromise));
    return exports;
}
