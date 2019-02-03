#include "whole.h"


void PrintMorfo(list<freeling::sentence> &ls) {
    freeling::word::const_iterator a;
    freeling::sentence::const_iterator w;

    wcout<<L"----------- MORPHOLOGICAL INFORMATION -------------"<<endl;

    // print sentence XML tag
    for (list<freeling::sentence>::iterator is=ls.begin(); is!=ls.end(); is++) {

        wcout<<L"<SENT>"<<endl;
        // for each word in sentence
        for (w=is->begin(); w!=is->end(); w++) {

            // print word form, with PoS and lemma chosen by the tagger
            wcout<<L"  <WORD form=\""<<w->get_form();
            wcout<<L"\" lemma=\""<<w->get_lemma();
            wcout<<L"\" pos=\""<<w->get_tag();
            wcout<<L"\">"<<endl;

            // for each possible analysis in word, output lemma, tag and probability
            for (a=w->analysis_begin(); a!=w->analysis_end(); ++a) {

                // print analysis info
                wcout<<L"    <ANALYSIS lemma=\""<<a->get_lemma();
                wcout<<L"\" pos=\""<<a->get_tag();
                wcout<<L"\" prob=\""<<a->get_prob();
                wcout<<L"\"/>"<<endl;
            }

            // close word XML tag after list of analysis
            wcout<<L"  </WORD>"<<endl;
        }

        // close sentence XML tag
        wcout<<L"</SENT>"<<endl;
    }
}

list<freeling::sentence> morfo_an(const freeling::maco_options &opt,
                                  const list<freeling::word> &tokenized_words,
                                  const freeling::splitter &sp) {
    list<freeling::sentence> ls;
    freeling::maco morfo(opt);
    morfo.set_active_options (false, // UserMap
                             true, // NumbersDetection,
                             true, //  PunctuationDetection,
                             true, //  DatesDetection,
                             true, //  DictionarySearch,
                             true, //  AffixAnalysis,
                             false, //  CompoundAnalysis,
                             true, //  RetokContractions,
                             true, //  MultiwordsDetection,
                             true, //  NERecognition,
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

freeling::maco_options create_maco_opt(const wstring &path, const wstring &lang) {
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

freeling::splitter create_splitter(const wstring &path) {
    if (!file_exists(path+L"splitter.dat")) {
        throw "No splitter for selected language";
    }
    freeling::splitter sp(path+L"splitter.dat");
    return sp;
}

freeling::tokenizer create_tokenizer(const wstring &path) {
    if (!file_exists(path+L"tokenizer.dat")) {
        throw "No tokenizer for selected language";
    }
    freeling::tokenizer tk(path+L"tokenizer.dat");
    return tk;
}

list<freeling::sentence> freelingAddon::test_morfo_an() {
    list<freeling::sentence> result;

    try {
        wstring text = L"Это тестовое сообщение. Вот так!";
        wstring lang = L"ru";

        freeling::util::init_locale(L"default");
        wstring ipath = L"/usr/local/share/freeling/";
        wstring path = ipath + lang + L"/";

        freeling::maco_options opt = create_maco_opt(path, lang);
        freeling::splitter sp = create_splitter(path);
        freeling::tokenizer tk = create_tokenizer(path);

        list<freeling::word> lw = tk.tokenize(text);
        list<freeling::sentence> result = morfo_an(opt, lw, sp);

        //PrintMorfo(result);

    } catch(const exception &e) {
        cout << e.what() << endl;
    }
    return result;
}

Napi::Array freelingAddon::NAPIMorphoAn(const Napi::CallbackInfo& info) {

}
