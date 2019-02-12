#ifndef WHOLE_H
#define WHOLE_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "addon_utils.h"
#include "word.h"


namespace freelingAddon {
    Napi::Object Init(Napi::Env env, Napi::Object exports);
    Napi::Array NAPIMorphoAn(const Napi::CallbackInfo& info);
    freeling::splitter create_splitter(const wstring &path);
    freeling::tokenizer create_tokenizer(const wstring &path);
    freeling::maco_options create_maco_opt(const wstring &path, const wstring &lang);
    std::list<freeling::sentence> morfo_an(const freeling::maco_options &opt,
                                      const std::list<freeling::word> &tokenized_words,
                                      const freeling::splitter &sp);
    std::list<freeling::sentence> test_morfo_an();
}


#endif // WHOLE_H
