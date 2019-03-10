#include "sentence.h"


Napi::FunctionReference freelingAddon::WrappedSentence::constructor;

Napi::Object freelingAddon::WrappedSentence::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Sentence", {
        InstanceMethod("getSentence", &WrappedSentence::GetSentence),
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Sentence", func);
    return exports;
}


freeling::sentence* freelingAddon::WrappedSentence::GetInternalInstance() {
    return this->sentence_;
}

freelingAddon::WrappedSentence::WrappedSentence(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedSentence>(info)  {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
     try {
        if(info.Length()&&info.Length()==1) {
            if ( info[0].IsExternal() ) {
                Napi::External<freeling::sentence> object_parent = info[0].As<Napi::External<freeling::sentence>>();
                freeling::sentence*input_sentence=object_parent.Data();
                this->sentence_ = input_sentence;
            }
            else if (info[0].IsArray()) {

                if(info[0].As<Napi::Array>().Length()>0) {
                    Napi::Array input_words_arr = info[0].As<Napi::Array>();
                    std::list<freeling::word> words = WrappedWord::getWordsList(env, input_words_arr);
                    this->sentence_ = new freeling::sentence(words);
                }
                else throw Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS);
            }
            else throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
        }
        else throw Napi::TypeError::New(env,WRONG_ARGUMENT_NUMBER);
     }
     catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
         
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}


Napi::Object freelingAddon::WrappedSentence::NewInstance(Napi::Env env, Napi::Value arg) {
  Napi::Object obj = constructor.New({ arg });
  return obj;
}

Napi::Value freelingAddon::WrappedSentence::GetSentence(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);    
    try {
        uint32_t i = 0;
        Napi::Array sentence = Napi::Array::New(env);
        freeling::sentence*sent=this->sentence_;
        for (freeling::sentence::const_iterator w=sent->begin();w != sent->end(); w++) {
            freeling::word *word_ = new freeling::word(*w);
            Napi::Object value = freelingAddon::WrappedWord::NewInstance(env, Napi::External<freeling::word>::New(env, word_));
            sentence.Set(i, value);
            word_=NULL;
            delete word_;
            i++;
        }
       return sentence;
    }
    catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
    
}

std::list<freeling::sentence> freelingAddon::WrappedSentence::getSentencesList(Napi::Env env, Napi::Array js_arg) {
    std::list<freeling::sentence> sentences;
    for (uint32_t i = 0; i < js_arg.Length(); i++) {
        if (js_arg.Get(i).IsObject()) {
            Napi::Object object_parent = js_arg.Get(i).As<Napi::Object>();
            freelingAddon::WrappedSentence* parent = Napi::ObjectWrap<freelingAddon::WrappedSentence>::Unwrap(object_parent);
            freeling::sentence* sentence_item = parent->GetInternalInstance();
            sentences.push_back(*sentence_item);
        } else
            throw Napi::TypeError::New(env, MUST_BE_AN_ARRAY_OF_SENTENCES);
    }
    return sentences;
}
