#include "async_splitter.h"

freelingAddon::AsyncSplitter::AsyncSplitter(Napi::Function& callback, Napi::Promise::Deferred deferred):
                                  Napi::AsyncWorker(callback), deferred(deferred) {};

void freelingAddon::AsyncSplitter::SetInputWordsList(const std::list<freeling::word> &input_words) {
    input_words_ = input_words;
}

void freelingAddon::AsyncSplitter::SetSplitter(const std::wstring&lpath) {
    this->splitter_ = new freeling::splitter(lpath);
}

Napi::Array freelingAddon::AsyncSplitter::getSplitSentences(Napi::Env env){
    Napi::Array splitted_ls = Napi::Array::New(env);
    try {
        uint32_t i = 0;

        for (list<freeling::sentence>::const_iterator is = this->splitted_sentences_.begin(); is != this->splitted_sentences_.end(); is++) {
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
    } catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    } catch( ... ) {
        deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
    }
    return splitted_ls;
}

freelingAddon::AsyncSplitter::~AsyncSplitter(){
    delete splitter_;
};

void freelingAddon::CallAsyncSplitterPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred) {
    Napi::String input_path = info[0].As<Napi::String>();
    Napi::Array input_words_arr = info[1].As<Napi::Array>();
    std::list<freeling::word> words = WrappedWord::getWordsList(env, input_words_arr);
    if(input_path.Utf8Value().length() != 0 && input_words_arr.Length() != 0) {
        std::wstring lpath = freeling::util::string2wstring(input_path.Utf8Value());
        if(addonUtil::file_exists(lpath)) {
            freeling::util::init_locale(L"default");
            Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
            AsyncSplitter* worker = new AsyncSplitter(callback, deferred);
            worker->SetSplitter(lpath);
            worker->SetInputWordsList(words);
            worker->Queue();
        } else
            deferred.Reject(Napi::TypeError::New(env, WRONG_CONFIG_PATH).Value());
    } else
        deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
    return;
}

Napi::Promise freelingAddon::CallAsyncSplitterPromise(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    try {
        if (info.Length() == 2) {
            if (info[0].IsString() && info[1].IsArray()) {
                CallAsyncSplitterPromiseInternal(info, env, deferred);
            } else
                deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE).Value());
        } else
            deferred.Reject(Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER).Value());
    } catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    } catch( ... ) {
        deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
    }
    return deferred.Promise();
}

Napi::Object freelingAddon::InitAsyncSplitter(Napi::Env env,Napi::Object exports) {
    exports.Set("split", Napi::Function::New(env, CallAsyncSplitterPromise));
    return exports;
}
