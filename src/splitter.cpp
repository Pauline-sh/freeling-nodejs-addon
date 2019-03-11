#include "splitter.h"


Napi::FunctionReference freelingAddon::WrappedSplitter::constructor;

Napi::Object freelingAddon::WrappedSplitter::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Splitter", {});

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Splitter", func);
    return exports;
}

Napi::Object freelingAddon::WrappedSplitter::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::Object obj = constructor.New({ arg });
    return obj;
}

freeling::splitter* freelingAddon::WrappedSplitter::GetInternalInstance() {
    return this->splitter_;
}

freelingAddon::WrappedSplitter::WrappedSplitter(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedSplitter>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if (info.Length() == 1) {
            if (info[0].IsString()) {
                Napi::String input_path = info[0].As<Napi::String>();
                std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
                if(addonUtil::file_exists(lpath)) {
                    freeling::util::init_locale(L"default");
                    this->splitter_ = new freeling::splitter(lpath);
                } else
                    throw Napi::TypeError::New(env, WRONG_CONFIG_PATH);
            } else {
                throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
            }
        } else {
            throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
        }
    } catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

freelingAddon::WrappedSplitter::~WrappedSplitter() {
    delete this->splitter_;
}

// === PROMISE === //

freelingAddon::AsyncSplitter::AsyncSplitter(Napi::Function& callback, Napi::Promise::Deferred deferred):
                                  Napi::AsyncWorker(callback), deferred(deferred) {};

void freelingAddon::AsyncSplitter::SetInputWordsList(const std::list<freeling::word> &input_words) {
    input_words_ = input_words;
}

void freelingAddon::AsyncSplitter::SetSplitter(const Napi::Object &object_parent) {
    WrappedSplitter* parent = Napi::ObjectWrap<freelingAddon::WrappedSplitter>::Unwrap(object_parent);
    this->splitter_ = parent->GetInternalInstance();
}

Napi::Array freelingAddon::AsyncSplitter::getSplitSentences(Napi::Env env){
    Napi::Array splitted_ls = Napi::Array::New(env);
    try {
        uint32_t i = 0;
        for (list<freeling::sentence>::const_iterator is = this->splitted_sentences_.begin(); is != this->splitted_sentences_.end(); is++) {
            freeling::sentence* sentence_ = new freeling::sentence(*is);
            Napi::Object value = freelingAddon::WrappedSentence::NewInstance(env, Napi::External<freeling::sentence>::New(env, sentence_));
            splitted_ls.Set(i, value);
            sentence_ = NULL;
            delete sentence_;
            i++;
        }
    } catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    } catch (const std::exception &exc) {
        deferred.Reject(Napi::TypeError::New(env, exc.what()).Value());
    }
    return splitted_ls;
}

void freelingAddon::CallAsyncSplitterPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred) {
    Napi::Object object_parent = info[0].As<Napi::Object>();
    if(object_parent.InstanceOf(WrappedSplitter::constructor.Value())) {
        Napi::Array input_words_arr = info[1].As<Napi::Array>();
        if(input_words_arr.Length() != 0) {
            std::list<freeling::word> words = WrappedWord::getWordsList(env, input_words_arr);
            freeling::util::init_locale(L"default");
            Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
            AsyncSplitter* worker = new AsyncSplitter(callback, deferred);
            worker->SetSplitter(object_parent);
            worker->SetInputWordsList(words);
            worker->Queue();
        } else
            deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
    } else
        deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
    return;
}

Napi::Promise freelingAddon::CallAsyncSplitterPromise(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    try {
        if (info.Length() == 2) {
            if (info[0].IsObject() && info[1].IsArray()) {
                CallAsyncSplitterPromiseInternal(info, env, deferred);
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

Napi::Object freelingAddon::InitAsyncSplitter(Napi::Env env,Napi::Object exports) {
    exports.Set("split", Napi::Function::New(env, CallAsyncSplitterPromise));
    return exports;
}
