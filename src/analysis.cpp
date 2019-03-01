#include "analysis.h"

Napi::FunctionReference freelingAddon::WrappedAnalysis::constructor;

Napi::Object freelingAddon::WrappedAnalysis::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Analysis", {
        InstanceMethod("hasProb", &WrappedAnalysis::HasProb),
        InstanceMethod("hasDistance", &WrappedAnalysis::HasDistance),
        InstanceMethod("getLemma", &WrappedAnalysis::GetLemma),
        InstanceMethod("getTag", &WrappedAnalysis::GetTag),
        InstanceMethod("getProb", &WrappedAnalysis::GetProb),
        InstanceMethod("getDistance", &WrappedAnalysis::GetDistance),
        InstanceMethod("isRetokenizable", &WrappedAnalysis::IsRetokenizable),
        InstanceMethod("getRetokenizable", &WrappedAnalysis::GetRetokenizable)

    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Analysis", func);
    return exports;
}

freeling::analysis* freelingAddon::WrappedAnalysis::GetInternalInstance() {
    return this->analysis_;
}

freelingAddon::WrappedAnalysis::WrappedAnalysis(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedAnalysis>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
       if(info.Length()==1) {
           if ( info[0].IsExternal() ) {
                   Napi::External<freeling::analysis> object_parent = info[0].As<Napi::External<freeling::analysis>>();
                   freeling::analysis*a=object_parent.Data();
                   analysis_=new freeling::analysis();
                   analysis_ = a;
               }
           else  {
               throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
           }
       }
       else {
           throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
       }

    }
    catch(Napi::TypeError &exc) {
            exc.ThrowAsJavaScriptException();
        }
    catch(...) {
            Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}


Napi::Object freelingAddon::WrappedAnalysis::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::Object obj = constructor.New({ arg });
  return obj;
}

Napi::Value freelingAddon::WrappedAnalysis::HasProb(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        bool has_prob = analysis_->has_prob();
        return Napi::Boolean::New(info.Env(), has_prob);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
  }

Napi::Value freelingAddon::WrappedAnalysis::HasDistance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        bool has_distance = analysis_->has_distance();
        return Napi::Boolean::New(info.Env(), has_distance);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
  }

Napi::Value freelingAddon::WrappedAnalysis::GetLemma(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        std::string lemma=freeling::util::wstring2string(analysis_->get_lemma());
        return Napi::String::New(env, lemma);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

Napi::Value freelingAddon::WrappedAnalysis::GetTag(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        std::string tag=freeling::util::wstring2string(analysis_->get_tag());
        return Napi::String::New(env, tag);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

Napi::Value freelingAddon::WrappedAnalysis::GetProb(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        double prob=analysis_->get_prob();
        return Napi::Number::New(env, prob);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

Napi::Value freelingAddon::WrappedAnalysis::GetDistance(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        double distance=analysis_->get_distance();
        return Napi::Number::New(env, distance);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

Napi::Value freelingAddon::WrappedAnalysis::IsRetokenizable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        bool is_retokenizable = analysis_->is_retokenizable();
        return Napi::Boolean::New(info.Env(), is_retokenizable);
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
  }


Napi::Value freelingAddon::WrappedAnalysis::GetRetokenizable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        uint32_t i=0;
        Napi::Array retok_ = Napi::Array::New(env);
        list<freeling::word> retok=analysis_->get_retokenizable();
        for (list<freeling::word>::const_iterator w=retok.begin(); w!=retok.end(); w++) {
             freeling::word*word_=new freeling::word(*w);
             Napi::Object value =
               freelingAddon::WrappedWord::NewInstance(env,Napi::External<freeling::word>::New(env,word_));
             retok_.Set(i,value);
             word_=NULL;
             delete word_;
             i++;
         }
         return retok_;
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
  }
