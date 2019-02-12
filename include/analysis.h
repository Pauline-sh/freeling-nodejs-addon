#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>
#include <napi.h>
//#include <boost/lexical_cast.hpp>
#include "freeling.h"
#include "word.h"
#include "whole.h"

namespace freelingAddon {
  Napi::Object GetWordAnalyses(Napi::Env env,freeling::word w);
  Napi::Object GetAnalyses(const Napi::CallbackInfo& info);
  Napi::Object InitWordAnalyses(Napi::Env env, Napi::Object exports);
};
#endif
