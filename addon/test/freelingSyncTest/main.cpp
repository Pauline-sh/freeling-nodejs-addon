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

// 1 millisecond = 1000 microseconds

int main()
{
    freeling::util::init_locale(L"default");
    wstring cfg = L"/usr/local/share/freeling/ru/";

    wstring text1658tokens = get_text_from_file("../text1658tokens.txt");
    wstring text8368tokens = get_text_from_file("../text8368tokens.txt");

    // tokenizer //
    auto constructorDurationStart = high_resolution_clock::now();
    freeling::tokenizer *the_tokenizer = new freeling::tokenizer(cfg + L"tokenizer.dat");
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
    freeling::splitter *the_splitter = new freeling::splitter(cfg + L"splitter.dat");
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

    return 0;
}
