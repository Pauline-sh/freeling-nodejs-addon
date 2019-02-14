#include "splitter.h"


Napi::FunctionReference freelingAddon::WrappedSplitter::constructor;

Napi::Object freelingAddon::WrappedSplitter::Init(Napi::Env env, Napi::Object exports){
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Splitter", {
        InstanceMethod("split", &WrappedSplitter::Split),
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
                bool file_exist = file_exists(lpath);
                if (file_exist) {
                    freeling::util::init_locale(L"default");
                    this->splitter_ = new freeling::splitter(lpath);
                } else
                    throw Napi::TypeError::New(env, "Config file doesn't exist");
            } else
                throw Napi::TypeError::New(env, "Parameter should be a string");
        } else
            throw Napi::TypeError::New(env, "Required parameter is not provided");
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

Napi::Value freelingAddon::WrappedSplitter::Split(const Napi::CallbackInfo &info){

}
