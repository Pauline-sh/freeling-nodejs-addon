#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <napi.h>
#include "freeling.h"
#include "freeling/morfo/tokenizer.h"
#include "addon_utils.h"
#include "word.h"

namespace freelingAddon {
  class WrappedTokenizer:public Napi::ObjectWrap<WrappedTokenizer> {
      public:
          static Napi::Object Init(Napi::Env env, Napi::Object exports);
          WrappedTokenizer(const Napi::CallbackInfo& info);
        private:
          freeling::tokenizer* GetInternalInstance();
          static Napi::FunctionReference constructor;
          /// tokenize string, return result as list
          ///std::list<word> tokenize(const std::wstring &text) const;
          Napi::Value Tokenize(const Napi::CallbackInfo&info);
          Napi::Array getTokens(Napi::Env env,const std::wstring&text);
          freeling::tokenizer*tokenizer_;
  };
};


/*
/// Constructor
  tokenizer(const std::wstring &cfgfile);
  /// tokenize string, leave result in lw
  void tokenize(const std::wstring &text, std::list<word> &lw) const;
  /// tokenize string, updating byte offset. Leave results in lw.
  void tokenize(const std::wstring &text, unsigned long &offset, std::list<word> &lw) const;
  /// tokenize string, updating offset, return result as list
  std::list<word> tokenize(const std::wstring &text, unsigned long &offset) const;*/
#endif
