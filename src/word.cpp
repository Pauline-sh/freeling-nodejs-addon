#include "word.h"

Napi::FunctionReference freelingAddon::WrappedWord::constructor;

Napi::Object freelingAddon::WrappedWord::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Word", {
        InstanceMethod("isMultiword", &WrappedWord::IsMultiword),
        InstanceMethod("getForm", &WrappedWord::GetForm),
        InstanceMethod("getLcForm", &WrappedWord::GetLcForm),
        InstanceMethod("getPhForm", &WrappedWord::GetPhForm),
        InstanceMethod("getLemma", &WrappedWord::GetLemma),
        InstanceMethod("getTag", &WrappedWord::GetTag),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Word", func);
    return exports;
}

freeling::word* freelingAddon::WrappedWord::GetInternalInstance() {
    return this->word_;
}

void freelingAddon::WrappedWord::createWrappedWord1arg(const Napi::CallbackInfo &info, Napi::Env env) {
    if ( info[0].IsString() ) {
        Napi::String js_arg = info[0].As<Napi::String>();
        std::wstring arg = convert_string_to_wstring(js_arg.Utf8Value());
        this->word_ = new freeling::word(arg);
    } else if ( info[0].IsExternal() ) {
        Napi::External<freeling::word> object_parent = info[0].As<Napi::External<freeling::word>>();
        freeling::word*w=object_parent.Data();
        this->word_ = w;//new freeling::word(w);
    } else if ( info[0].IsObject() ) {
        Napi::Object object_parent = info[0].As<Napi::Object>();
        WrappedWord* parent = Napi::ObjectWrap<freelingAddon::WrappedWord>::Unwrap(object_parent);
        freeling::word* arg = parent->GetInternalInstance();
        this->word_ = new freeling::word(*arg);
    } else {
        throw Napi::TypeError::New(env, "Argument must be either a string or an instance of Word");
    }
    return;
}

void freelingAddon::WrappedWord::createWrappedWord2args(const Napi::CallbackInfo &info, Napi::Env env) {
    if ( info[0].IsString() && info[1].IsArray() ) {
        Napi::String js_arg1 = info[0].As<Napi::String>();
        std::wstring arg1 = convert_string_to_wstring(js_arg1.Utf8Value());

        std::list<freeling::word> arg2;
        Napi::Array js_arg2 = info[1].As<Napi::Array>();
        uint32_t arr_len = js_arg2.Length();
        for (uint32_t i = 0; i < arr_len; i++) {
            if (js_arg2.Get(i).IsObject()) {
                Napi::Object object_parent = js_arg2.Get(i).As<Napi::Object>();
                freelingAddon::WrappedWord* parent = Napi::ObjectWrap<freelingAddon::WrappedWord>::Unwrap(object_parent);
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
    return;
}

freelingAddon::WrappedWord::WrappedWord(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedWord>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    try {
        switch(info.Length()) {

        case 0:
            this->word_ = new freeling::word();
            break;

        case 1:
            createWrappedWord1arg(info, env);
            break;

        case 2:
            createWrappedWord2args(info, env);
            break;

        case 3:
            // TODO: class analysis
            //word(const std::wstring &, const std::list<analysis> &, const std::list<word> &);
            throw Napi::TypeError::New(env, "Still in development");

        default:
            throw Napi::TypeError::New(env, "The maximum possible number of arguments is 3");
        }
    } catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    /*} catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();        
    }*/
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

Napi::Object freelingAddon::WrappedWord::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::Object obj = constructor.New({ arg });
  return obj;
}

Napi::Value freelingAddon::WrappedWord::GetForm(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string form = "";
    try {
        form=convert_wstring_to_string(this->word_->get_form());
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::String::New(info.Env(), form);
}

Napi::Value freelingAddon::WrappedWord::GetLcForm(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string lc_form = "";
    try {
        lc_form=convert_wstring_to_string(this->word_->get_lc_form());
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::String::New(info.Env(), lc_form);
}

Napi::Value freelingAddon::WrappedWord::GetPhForm(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string ph_form = "";
    try {
        ph_form=convert_wstring_to_string(this->word_->get_ph_form());
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::String::New(info.Env(), ph_form);
}

Napi::Value freelingAddon::WrappedWord::GetLemma(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string lemma = "";
    try {
        if (info.Length() == 0) {
            lemma=convert_wstring_to_string(this->word_->get_lemma());
        } else if (info.Length() == 1 && info[0].IsNumber()) {
            Napi::Number analysis = info[0].As<Napi::Number>();
            lemma=convert_wstring_to_string(this->word_->get_lemma(analysis.Int32Value()));
        } else {
            throw Napi::TypeError::New(env, "There must be no arguments or one integer argument");
        }
    } catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    } catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::String::New(info.Env(), lemma);
}

Napi::Value freelingAddon::WrappedWord::GetTag(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    std::string tag = "";
    try {
        if (info.Length() == 0) {
            tag=convert_wstring_to_string(this->word_->get_tag());
        } else if (info.Length() == 1 && info[0].IsNumber()) {
            Napi::Number analysis = info[0].As<Napi::Number>();
            tag=convert_wstring_to_string(this->word_->get_tag(analysis.Int32Value()));
        } else {
            throw Napi::TypeError::New(env, "There must be no arguments or one integer argument");
        }
    } catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    } catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::String::New(info.Env(), tag);
}

Napi::Value freelingAddon::WrappedWord::IsMultiword(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    bool result = true;
    try {
        result = this->word_->is_multiword();
    }
    catch(...) {
        Napi::TypeError::New(env, DEFAULT_ERR_MSG).ThrowAsJavaScriptException();
    }
    return Napi::Boolean::New(info.Env(), result);
}
