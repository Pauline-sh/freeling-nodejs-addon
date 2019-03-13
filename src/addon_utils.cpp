#include "addon_utils.h"
list<freeling::sentence> addonUtil::morfo_an(const freeling::maco_options &opt,
                                  const std::list<freeling::word> &tokenized_words,
                                  const freeling::splitter &sp) {
    list<freeling::sentence> ls;
    freeling::maco morfo(opt);
    morfo.set_active_options (false, // UserMap
                             false, // NumbersDetection,
                             true, //  PunctuationDetection,
                             false, //  DatesDetection,
                             true, //  DictionarySearch,
                             true, //  AffixAnalysis,
                             false, //  CompoundAnalysis,
                             true, //  RetokContractions,
                             true, //  MultiwordsDetection,
                             false, //  NERecognition,
                             false, //  QuantitiesDetection,
                             true);  //  ProbabilityAssignment
    freeling::splitter::session_id sid = sp.open_session();
    ls = sp.split(sid, tokenized_words, false);
    morfo.analyze(ls);
    list<freeling::sentence> result = ls;
    sp.split(sid, tokenized_words, true, ls);
    sp.close_session(sid);

    return result;
}

freeling::maco_options addonUtil::create_maco_opt(const wstring &path, const wstring &lang) {
    if (!file_exists(path)) {
        throw "No resources for selected language";
    }
    freeling::maco_options opt(lang);
    opt.UserMapFile=L"";
    opt.LocutionsFile=path+L"locucions.dat";
    opt.AffixFile=path+L"afixos.dat";
    opt.ProbabilityFile=path+L"probabilitats.dat";
    opt.DictionaryFile=path+L"dicc.src";
    opt.NPdataFile=path+L"np.dat";
    opt.PunctuationFile=path+L"../common/punct.dat";
    return opt;
}

freeling::splitter addonUtil::create_splitter(const wstring &path) {
    if (!file_exists(path+L"splitter.dat")) {
        throw "No splitter for selected language";
    }
    freeling::splitter sp(path+L"splitter.dat");
    return sp;
}

freeling::tokenizer addonUtil::create_tokenizer(const wstring &path) {
    if (!file_exists(path+L"tokenizer.dat")) {
        throw "No tokenizer for selected language";
    }
    freeling::tokenizer tk(path+L"tokenizer.dat");
    return tk;
}

Napi::Value addonUtil::EmptyCallback(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    return env.Undefined();
}

Napi::Array addonUtil::FreelingSentences2NapiArray(const std::list<freeling::sentence>&sentences, Napi::Env env){
        Napi::Array ls = Napi::Array::New(env);
        uint32_t i = 0;
        for (list<freeling::sentence>::const_iterator is = sentences.begin(); is != sentences.end(); is++) {
            freeling::sentence* sentence_ = new freeling::sentence(*is);
            Napi::Object value = freelingAddon::WrappedSentence::NewInstance(env, Napi::External<freeling::sentence>::New(env, sentence_));
            ls.Set(i, value);
            sentence_ = NULL;
            delete sentence_;
            i++;
        }
        return ls;
}
