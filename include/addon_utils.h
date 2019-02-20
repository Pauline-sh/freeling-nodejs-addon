#ifndef STRINGCONVERT_H
#define STRINGCONVERT_H

#include <string>
#include <locale>
#include <codecvt>
#include <freeling.h>
#include <napi.h>

#include "addon_errors.h"


namespace addonUtil {
    template<typename CheckType, typename InstanceType>
    bool isInstanceOf(const InstanceType &Instance) {
      return (dynamic_cast<CheckType *>(&Instance) != NULL);
    }

    inline bool file_exists(const std::wstring& name) {
        std::string fname = freeling::util::wstring2string(name);
        if (FILE *file = fopen(fname.c_str(), "r")) {
            fclose(file);
            return true;
        }
        return false;
    }


list<freeling::sentence> morfo_an(const freeling::maco_options &opt,
                                  const std::list<freeling::word> &tokenized_words,
                                  const freeling::splitter &sp);
freeling::maco_options create_maco_opt(const wstring &path, const wstring &lang);
freeling::splitter create_splitter(const wstring &path);
freeling::tokenizer create_tokenizer(const wstring &path);

Napi::Value EmptyCallback(const Napi::CallbackInfo& info);

}
#endif // STRINGCONVERT_H
