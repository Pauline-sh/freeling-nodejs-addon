#ifndef STRINGCONVERT_H
#define STRINGCONVERT_H

#include <string>
#include <locale>
#include <codecvt>
#include <freeling.h>

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

#endif // STRINGCONVERT_H
