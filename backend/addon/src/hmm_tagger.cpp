#include "hmm_tagger.h"

Napi::FunctionReference freelingAddon::WrappedHmmTagger::constructor;

Napi::Object freelingAddon::WrappedHmmTagger::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "HmmTagger", {});
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("HmmTagger", func);
    return exports;
}

Napi::Object freelingAddon::WrappedHmmTagger::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::Object obj = constructor.New({ arg });
    return obj;
}

freeling::hmm_tagger* freelingAddon::WrappedHmmTagger::GetInternalInstance() {
    return this->tagger_;
}

void freelingAddon::WrappedHmmTagger:: SetTagger(const Napi::CallbackInfo &info) {
    Napi::Env env=info.Env();
    try {
        Napi::String input_path = info[0].As<Napi::String>();
        std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
        bool file_exist=addonUtil::file_exists(lpath);
        if(file_exist){
              freeling::util::init_locale(L"default");
              bool rtk=info[1].As<Napi::Boolean>().Value();
              unsigned int force=info[2].As<Napi::Number>().Uint32Value();
              unsigned int kb=info[3].As<Napi::Number>().Uint32Value();
              this->tagger_=new freeling::hmm_tagger (lpath,rtk,force,kb);
        }
        else throw Napi::TypeError::New(env, WRONG_CONFIG_PATH);
    }
    catch(Napi::TypeError &exc) {
            exc.ThrowAsJavaScriptException();
    }
    catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

freelingAddon::WrappedHmmTagger::WrappedHmmTagger(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedHmmTagger>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
       if (4 == info.Length() ){
           if(info[0].IsString() && info[1].IsBoolean() && info[2].IsNumber() && info[3].IsNumber()) {
               SetTagger(info);
           }
           else {
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
    catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

freelingAddon::WrappedHmmTagger::~WrappedHmmTagger() {
    delete this->tagger_;
}

/********************************AsyncHmmTagger****************************************/

freelingAddon::AsyncHmmTagger::AsyncHmmTagger(Napi::Function& callback, Napi::Promise::Deferred deferred):
    Napi::AsyncWorker(callback), deferred(deferred) {};


void freelingAddon::AsyncHmmTagger::SetInputSentencesList(const std::list<freeling::sentence> &input_sentences) {
    this->input_sentences_ = input_sentences;
}

void freelingAddon::AsyncHmmTagger::SetHmmTagger(const Napi::Env env, const Napi::Object &object_parent) {
    WrappedHmmTagger* parent = Napi::ObjectWrap<freelingAddon::WrappedHmmTagger>::Unwrap(object_parent);
    this->tagger_ = parent->GetInternalInstance();
}


Napi::Object freelingAddon::InitAsyncHmmTagger(Napi::Env env, Napi::Object exports) {
    exports.Set("hmmTaggerAnalyze", Napi::Function::New(env, CallAsyncHmmTaggerPromise));
    return exports;
}

void freelingAddon::CallAsyncHmmTaggerPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred) {
    Napi::Object object_parent = info[0].As<Napi::Object>();
    if(object_parent.InstanceOf(WrappedHmmTagger::constructor.Value())) {
        Napi::Array input_sentences_arr = info[1].As<Napi::Array>();
        if(input_sentences_arr.Length() != 0) {
            std::list<freeling::sentence> sentences = WrappedSentence::getSentencesList(env, input_sentences_arr);
            freeling::util::init_locale(L"default");
            Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
            AsyncHmmTagger* worker = new AsyncHmmTagger(callback, deferred);
            worker->SetHmmTagger(env, object_parent);
            worker->SetInputSentencesList(sentences);
            worker->Queue();
        } else
            deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
    } else
        deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
    return;
}

Napi::Promise freelingAddon::CallAsyncHmmTaggerPromise(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    try {
        if (2 == info.Length()) {
            if (info[0].IsObject() && info[1].IsArray()) {
                CallAsyncHmmTaggerPromiseInternal(info, env, deferred);
            } else
                deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
        } else
            deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
    } catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    } catch (const std::exception &exc) {
        deferred.Reject(Napi::TypeError::New(env, exc.what()).Value());
    }
    return deferred.Promise();
}


