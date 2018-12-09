#ifndef STRINGCONVERT_H
#define STRINGCONVERT_H

#include <string>
#include <locale>
#include <codecvt>

std::wstring convert_string(std::string narrow_string);

std::string convert_wstring(std::wstring wide_string);

#endif // STRINGCONVERT_H
