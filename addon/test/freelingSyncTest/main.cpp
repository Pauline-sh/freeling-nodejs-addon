#include <iostream>
#include <fstream>
#include <chrono>

#include "freeling.h"

using namespace std;
using namespace std::chrono;

wstring get_text_from_file(string filename) {
    ifstream the_file(filename);
    std::stringstream buffer;
    buffer << the_file.rdbuf();
    the_file.close();
    return freeling::util::string2wstring(buffer.str());
}

freeling::maco_options my_maco_options(const wstring &lang, const wstring &path) {
   // create options pack
   freeling::maco_options opt(lang);
   // fill it with files for morphological submodules. Only those that are going
   // to be used need to be provided.
   opt.UserMapFile = L"";
   opt.LocutionsFile = path + L"locucions.dat";
   opt.AffixFile = path + L"afixos.dat";
   opt.ProbabilityFile = path + L"probabilitats.dat";
   opt.DictionaryFile = path + L"dicc.src";
   opt.NPdataFile = path + L"np.dat";
   opt.PunctuationFile = path + L"../common/punct.dat";

   return opt;
}

// 1 millisecond = 1000 microseconds

int main()
{
    freeling::util::init_locale(L"default");
    wstring cfg = L"/usr/local/share/freeling/";
    wstring lang = L"ru";

    wstring text1658tokens = get_text_from_file("../text1658tokens.txt");
    wstring text8368tokens = get_text_from_file("../text8368tokens.txt");

    // tokenizer //
    auto constructorDurationStart = high_resolution_clock::now();
    freeling::tokenizer *the_tokenizer = new freeling::tokenizer(cfg + lang + L"/tokenizer.dat");
    auto constructorDuration = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(constructorDuration - constructorDurationStart).count();
    cout << "tokenizer constructor execution duration: " << duration << " microseconds" << endl;

    auto analyzeDurationStart = high_resolution_clock::now();
    list<freeling::word> lw1658tokens = the_tokenizer->tokenize(text1658tokens);
    auto analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "tokenize 1658 tokens execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    list<freeling::word> lw8368tokens = the_tokenizer->tokenize(text8368tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "tokenize 8368 tokens execution duration: " << duration << " microseconds" << endl;

    // splitter //
    constructorDurationStart = high_resolution_clock::now();
    freeling::splitter *the_splitter = new freeling::splitter(cfg + lang + L"/splitter.dat");
    constructorDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(constructorDuration - constructorDurationStart).count();
    cout << "splitter constructor execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    list<freeling::sentence> ls1658tokens = the_splitter->split(lw1658tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "split 1658 tokens execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    list<freeling::sentence> ls8368tokens  = the_splitter->split(lw8368tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "split 8368 tokens execution duration: " << duration << " microseconds" << endl;

    // maco //
    constructorDurationStart = high_resolution_clock::now();
    freeling::maco *the_morfo = new freeling::maco(my_maco_options(lang, cfg + lang + L"/"));
    constructorDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(constructorDuration - constructorDurationStart).count();
    cout << "maco constructor execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    the_morfo->analyze(ls1658tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "analyze 1658 tokens execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    the_morfo->analyze(ls8368tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "analyze 8368 tokens execution duration: " << duration << " microseconds" << endl;

    // hmm tagger //
    constructorDurationStart = high_resolution_clock::now();
    freeling::hmm_tagger *the_tagger = new freeling::hmm_tagger(cfg + lang + L"/tagger.dat", true, FORCE_TAGGER);
    constructorDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(constructorDuration - constructorDurationStart).count();
    cout << "maco constructor execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    the_tagger->analyze(ls1658tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "analyze 1658 tokens execution duration: " << duration << " microseconds" << endl;

    analyzeDurationStart = high_resolution_clock::now();
    the_tagger->analyze(ls8368tokens);
    analyzeDuration = high_resolution_clock::now();
    duration = duration_cast<microseconds>(analyzeDuration - analyzeDurationStart).count();
    cout << "analyze 8368 tokens execution duration: " << duration << " microseconds" << endl;

    return 0;
}
