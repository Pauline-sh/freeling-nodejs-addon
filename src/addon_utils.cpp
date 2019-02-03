#include "stringconvert.h"

std::wstring convert_string(const std::string &narrow_string){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wide_string = converter.from_bytes(narrow_string);
    return wide_string;
}

std::string convert_wstring(const std::wstring wide_string){
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string narrow_string = converter.to_bytes(wide_string);
    return narrow_string;
}
