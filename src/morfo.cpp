#include "morfo.h"


Napi::FunctionReference freelingAddon::WrappedMorfo::constructor;

Napi::Object freelingAddon::WrappedMorfo::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Morfo", {
        InstanceMethod("setActiveOptions", &WrappedMorfo::SetActiveOptions),
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Morfo", func);
    return exports;
}

Napi::Object freelingAddon::WrappedMorfo::NewInstance(Napi::Env env, Napi::Value arg) {
    Napi::Object obj = constructor.New({ arg });
    return obj;
}

freeling::maco* freelingAddon::WrappedMorfo::GetInternalInstance() {
    return this->morfo_;
}

freelingAddon::WrappedMorfo::WrappedMorfo(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WrappedMorfo>(info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        if (info.Length() == 2) {
            if (info[0].IsString() && info[1].IsString()) {
                freeling::maco_options opt = GetMacoOpt(env, info[0].As<Napi::String>(), info[1].As<Napi::String>());
                this->morfo_ = new freeling::maco(opt);
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

freeling::maco_options freelingAddon::WrappedMorfo::GetMacoOpt(Napi::Env env, const string &path_to_freeling, const string &lang) {
    const wstring path_to_freeling_ = freeling::util::string2wstring(path_to_freeling);
    const wstring lang_ = freeling::util::string2wstring(lang);
    const wstring path_ = path_to_freeling_ + lang_ + L"/";

    if (!addonUtil::file_exists(path_)) {
        throw Napi::TypeError::New(env, NO_RESOURCES_FOR_SELECTED_LANG);
    }
    freeling::maco_options opt(lang_);
    opt.UserMapFile = L"";
    opt.LocutionsFile = path_ + L"locucions.dat";
    opt.AffixFile = path_ + L"afixos.dat";
    opt.ProbabilityFile = path_ + L"probabilitats.dat";
    opt.DictionaryFile = path_ + L"dicc.src";
    opt.NPdataFile = path_ + L"np.dat";
    opt.PunctuationFile = path_ + L"../common/punct.dat";
    return opt;
}

freelingAddon::WrappedMorfo::~WrappedMorfo() {
    delete this->morfo_;
}

void freelingAddon::WrappedMorfo::SetActiveOptions(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    try {
        const uint32_t opts_size = 12;
        bool active_opts_arr[opts_size] = { false, true, true, true, true, true, false, true, true, true, false, true };
        if (info.Length() == 1) {
            if (info[0].IsObject()) {
                Napi::Object active_opts_ = info[0].As<Napi::Object>();
                if (active_opts_.Has("UserMap") && active_opts_.Has("NumbersDetection") && active_opts_.Has("PunctuationDetection") && active_opts_.Has("DatesDetection") &&
                        active_opts_.Has("DictionarySearch") && active_opts_.Has("AffixAnalysis") && active_opts_.Has("CompoundAnalysis") && active_opts_.Has("RetokContractions") &&
                        active_opts_.Has("MultiwordsDetection") && active_opts_.Has("NERecognition") && active_opts_.Has("QuantitiesDetection") && active_opts_.Has("ProbabilityAssignment")) {
                    active_opts_arr[0] = active_opts_.Get("UserMap").As<Napi::Boolean>();
                    active_opts_arr[1] = active_opts_.Get("NumbersDetection").As<Napi::Boolean>();
                    active_opts_arr[2] = active_opts_.Get("PunctuationDetection").As<Napi::Boolean>();
                    active_opts_arr[3] = active_opts_.Get("DatesDetection").As<Napi::Boolean>();
                    active_opts_arr[4] = active_opts_.Get("DictionarySearch").As<Napi::Boolean>();
                    active_opts_arr[5] = active_opts_.Get("AffixAnalysis").As<Napi::Boolean>();
                    active_opts_arr[6] = active_opts_.Get("CompoundAnalysis").As<Napi::Boolean>();
                    active_opts_arr[7] = active_opts_.Get("RetokContractions").As<Napi::Boolean>();
                    active_opts_arr[8] = active_opts_.Get("MultiwordsDetection").As<Napi::Boolean>();
                    active_opts_arr[9] = active_opts_.Get("NERecognition").As<Napi::Boolean>();
                    active_opts_arr[10] = active_opts_.Get("QuantitiesDetection").As<Napi::Boolean>();
                    active_opts_arr[11] = active_opts_.Get("ProbabilityAssignment").As<Napi::Boolean>();
                } else {
                    throw Napi::TypeError::New(env, WRONG_PROPERTIES_FOR_ACTIVE_OPTS);
                }
            } else {
                throw Napi::TypeError::New(env, WRONG_ARGUMENT_TYPE);
            }
        } else if (info.Length() == 0) {
            // nothing to do, proceed to use default opts
        } else {
            throw Napi::TypeError::New(env, WRONG_ARGUMENT_NUMBER);
        }
        this->morfo_->set_active_options(active_opts_arr[0], // UserMap
                                         active_opts_arr[1], // NumbersDetection,
                                         active_opts_arr[2], //  PunctuationDetection,
                                         active_opts_arr[3], //  DatesDetection,
                                         active_opts_arr[4], //  DictionarySearch,
                                         active_opts_arr[5], //  AffixAnalysis,
                                         active_opts_arr[6], //  CompoundAnalysis,
                                         active_opts_arr[7], //  RetokContractions,
                                         active_opts_arr[8], //  MultiwordsDetection,
                                         active_opts_arr[9], //  NERecognition,
                                         active_opts_arr[10], //  QuantitiesDetection,
                                         active_opts_arr[11]);  //  ProbabilityAssignment
    } catch(Napi::TypeError &exc) {
        exc.ThrowAsJavaScriptException();
    } catch (const std::exception &exc) {
        Napi::TypeError::New(env, exc.what()).ThrowAsJavaScriptException();
    }
}

/* кидает ошибку symbol lookup error
 * bool* SetActiveOptsArray(Napi::Env env, bool active_opts_arr[], const Napi::Object& active_opts_) {
    if (active_opts_.Has("UserMap") && active_opts_.Has("NumbersDetection") && active_opts_.Has("PunctuationDetection") && active_opts_.Has("DatesDetection") &&
            active_opts_.Has("DictionarySearch") && active_opts_.Has("AffixAnalysis") && active_opts_.Has("CompoundAnalysis") && active_opts_.Has("RetokContractions") &&
            active_opts_.Has("MultiwordsDetection") && active_opts_.Has("NERecognition") && active_opts_.Has("QuantitiesDetection") && active_opts_.Has("ProbabilityAssignment")) {

        active_opts_arr[0] = active_opts_.Get("UserMap").As<Napi::Boolean>();
        active_opts_arr[1] = active_opts_.Get("NumbersDetection").As<Napi::Boolean>();
        active_opts_arr[2] = active_opts_.Get("PunctuationDetection").As<Napi::Boolean>();
        active_opts_arr[3] = active_opts_.Get("DatesDetection").As<Napi::Boolean>();
        active_opts_arr[4] = active_opts_.Get("DictionarySearch").As<Napi::Boolean>();
        active_opts_arr[5] = active_opts_.Get("AffixAnalysis").As<Napi::Boolean>();
        active_opts_arr[6] = active_opts_.Get("CompoundAnalysis").As<Napi::Boolean>();
        active_opts_arr[7] = active_opts_.Get("RetokContractions").As<Napi::Boolean>();
        active_opts_arr[8] = active_opts_.Get("MultiwordsDetection").As<Napi::Boolean>();
        active_opts_arr[9] = active_opts_.Get("NERecognition").As<Napi::Boolean>();
        active_opts_arr[10] = active_opts_.Get("QuantitiesDetection").As<Napi::Boolean>();
        active_opts_arr[11] = active_opts_.Get("ProbabilityAssignment").As<Napi::Boolean>();
    } else {
        throw Napi::TypeError::New(env, WRONG_PROPERTIES_FOR_ACTIVE_OPTS);
    }
    return active_opts_arr;
}*/

// ==== PROMISE ==== //

Napi::Promise freelingAddon::CallAsyncMorfoPromise(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(info.Env());
    try {
        if (info.Length() == 2) {
            if (info[0].IsObject() && info[1].IsArray()) {
                CallAsyncMorfoPromiseInternal(info, env, deferred);
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

void freelingAddon::CallAsyncMorfoPromiseInternal(const Napi::CallbackInfo& info, const Napi::Env& env, const Napi::Promise::Deferred& deferred) {
    Napi::Object object_parent = info[0].As<Napi::Object>();
    Napi::Array input_sentences_arr = info[1].As<Napi::Array>();
    if(input_sentences_arr.Length() != 0) {
        std::list<freeling::sentence> sentences = WrappedSentence::getSentencesList(env, input_sentences_arr);
        freeling::util::init_locale(L"default");
        Napi::Function callback = Napi::Function::New(env, addonUtil::EmptyCallback);
        AsyncMorfo* worker = new AsyncMorfo(callback, deferred);
        worker->SetMorfo(env, object_parent);
        worker->SetInputSentencesList(sentences);
        worker->Queue();
    } else
        deferred.Reject(Napi::TypeError::New(env, NO_EMPTY_ARGUMENTS).Value());
    return;
}

Napi::Object freelingAddon::InitAsyncMorfo(Napi::Env env, Napi::Object exports) {
    exports.Set("morfoAnalyze", Napi::Function::New(env, CallAsyncMorfoPromise));
    return exports;
}

freelingAddon::AsyncMorfo::AsyncMorfo(Napi::Function& callback, Napi::Promise::Deferred deferred):
    Napi::AsyncWorker(callback), deferred(deferred) {};

Napi::Array freelingAddon::AsyncMorfo::getAnalyzedSentences(Napi::Env env) {
    Napi::Array analyzed_ls = Napi::Array::New(env);
    try {
        uint32_t i = 0;
        for (list<freeling::sentence>::const_iterator is = this->analyzed_sentences_.begin(); is != this->analyzed_sentences_.end(); is++) {
            freeling::sentence* sentence_ = new freeling::sentence(*is);
            Napi::Object value = freelingAddon::WrappedSentence::NewInstance(env, Napi::External<freeling::sentence>::New(env, sentence_));
            analyzed_ls.Set(i, value);
            sentence_ = NULL;
            delete sentence_;
            i++;
        }
    } catch(const Napi::TypeError &exc) {
        deferred.Reject(exc.Value());
    } catch( ... ) {
        deferred.Reject(Napi::TypeError::New(env, DEFAULT_ERR_MSG).Value());
    }
    return analyzed_ls;
}

void freelingAddon::AsyncMorfo::SetInputSentencesList(const std::list<freeling::sentence> &input_sentences) {
    this->input_sentences_ = input_sentences;
}

void freelingAddon::AsyncMorfo::SetMorfo(const Napi::Env env, const Napi::Object &object_parent) {
    WrappedMorfo* parent = Napi::ObjectWrap<freelingAddon::WrappedMorfo>::Unwrap(object_parent);
    this->morfo_ = parent->GetInternalInstance();
}
