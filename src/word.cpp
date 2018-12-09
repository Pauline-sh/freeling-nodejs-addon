#include "word.h"

Napi::FunctionReference freelingAddon::Word::constructor;

Napi::Object freelingAddon::Word::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Word", {
        InstanceMethod("isMultiword", &Word::IsMultiword),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Word", func);
    return exports;
}

freeling::word* freelingAddon::Word::GetInternalInstance() {
    return this->word_;
}

freelingAddon::Word::Word(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Word>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    try {
        switch(info.Length()) {
        case 0:
            this->word_ = new freeling::word();
            break;
        case 1:
            if ( info[0].IsString() ) {
                Napi::String js_arg = info[0].As<Napi::String>();
                std::wstring arg = convert_string(js_arg.Utf8Value());
                this->word_ = new freeling::word(arg);
            } else {
                Napi::Object object_parent = info[0].As<Napi::Object>();
                freelingAddon::Word* parent = Napi::ObjectWrap<freelingAddon::Word>::Unwrap(object_parent);
                freeling::word* arg = parent->GetInternalInstance();
                this->word_ = new freeling::word(*arg);
            }
            break;
        case 2:
            if ( info[0].IsString() && info[1].IsArray() ) {
                Napi::String js_arg1 = info[0].As<Napi::String>();
                std::wstring arg1 = convert_string(js_arg1.Utf8Value());

                std::list<freeling::word> arg2;
                Napi::Array js_arg2 = info[1].As<Napi::Array>();
                uint32_t arr_len = js_arg2.Length();
                for (uint32_t i = 0; i < arr_len; i++){
                    if (js_arg2.Get(i).IsObject()) {
                        Napi::Object object_parent = js_arg2.Get(i).As<Napi::Object>();
                        freelingAddon::Word* parent = Napi::ObjectWrap<freelingAddon::Word>::Unwrap(object_parent);
                        freeling::word* word_item = parent->GetInternalInstance();
                        arg2.push_back(*word_item);
                    } else {
                        throw Napi::TypeError::New(env, "Array must consist of objects of class Word");
                    }
                }
                this->word_ = new freeling::word(arg1, arg2);
            } else {
                throw Napi::TypeError::New(env, "The first argument must be a string and the second must be an array of Words");
            }
            break;
        case 3:
            // TODO: class analysis
            //word(const std::wstring &, const std::list<analysis> &, const std::list<word> &);
            throw Napi::TypeError::New(env, "Still in development");
        default:
            throw Napi::TypeError::New(env, "The maximum possible number of arguments is 4");
        }
    } catch(Napi::TypeError exception_) {
        exception_.ThrowAsJavaScriptException();
    }
}

Napi::Value freelingAddon::Word::IsMultiword(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    bool result = this->word_->is_multiword();

    return Napi::Boolean::New(info.Env(), result);
}

