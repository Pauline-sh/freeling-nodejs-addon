#include "splitter.h"


Napi::FunctionReference freelingAddon::WrappedSplitter::constructor;

Napi::Object freelingAddon::WrappedSplitter::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Splitter", {
        InstanceMethod("split", &WrappedSplitter::Split),
        //InstanceMethod("openSession", &WrappedSplitter::OpenSession),
        //InstanceMethod("closeSession", &WrappedSplitter::CloseSession),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Splitter", func);
    return exports;
}

freelingAddon::WrappedSplitter::WrappedSplitter(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedSplitter>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if(info.Length() == 1) {
            if(info[0].IsString()) {
                Napi::String input_path = info[0].As<Napi::String>();
                std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
                bool file_exist = addonUtil::file_exists(lpath);
                if (file_exist) {
                    freeling::util::init_locale(L"default");
                    this->splitter_ = new freeling::splitter(lpath);
                } else
                    throw Napi::TypeError::New(env, WRONG_CONFIG_PATH);
            } else
                throw Napi::TypeError::New(env, MUST_BE_A_STRING);
        } else
            throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
    }
    catch(const Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    }
    catch( ... ) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
}

freeling::splitter* freelingAddon::WrappedSplitter::getInternalInstance(){
    return this->splitter_;
}

Napi::Array freelingAddon::WrappedSplitter::getSplitSentences(Napi::Env env, std::list<freeling::word> words) {
    std::list<freeling::sentence> ls = this->splitter_->split(words);
    Napi::Array splitted_ls = Napi::Array::New(env);

    uint32_t i = 0;
    for (list<freeling::sentence>::const_iterator is = ls.begin(); is != ls.end(); is++) {
        Napi::Array sentence = Napi::Array::New(env);
        uint32_t j = 0;
        for (freeling::sentence::const_iterator w = is->begin(); w != is->end(); w++) {
            freeling::word *word_ = new freeling::word(*w);
            Napi::Object value = freelingAddon::WrappedWord::NewInstance(env, Napi::External<freeling::word>::New(env, word_));
            sentence.Set(j, value);
            delete word_;
            j++;
        }
        splitted_ls.Set(i, sentence);
        i++;
    }
    return splitted_ls;
}

Napi::Value freelingAddon::WrappedSplitter::Split(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if (info.Length() == 1) {
            if (info[0].IsArray()) {
                Napi::Array js_arg = info[0].As<Napi::Array>();
                std::list<freeling::word> words = WrappedWord::getWordsList(env, js_arg);
                return getSplitSentences(env, words);
            } else
                throw Napi::TypeError::New(env, MUST_BE_AN_ARRAY_OF_WORDS);
        } else if (info.Length() == 3) {
            throw Napi::TypeError::New(env, IN_DEVELOPMENT);
        } else
            throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
    } catch (Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

/*Napi::Value freelingAddon::WrappedSplitter::OpenSession(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if (info.Length() == 0) {
            freeling::splitter::session_id sess_id = this->splitter_->open_session();
            Napi::External<freeling::splitter::session_id> sess_id_ =
                Napi::External<freeling::splitter::session_id>::New(info.Env(), &sess_id);
            return sess_id_;
        }
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}*/

/*void freelingAddon::WrappedSplitter::CloseSession(const Napi::CallbackInfo &info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if (info.Length() == 1 && info[0].IsExternal()) {
            freeling::splitter::session_id *sess_id = info[0].As<Napi::External<freeling::splitter::session_id>>().Data();
            this->splitter_->close_session(*sess_id);
            return;
        } else
            throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}*/
