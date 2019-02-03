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

    std::list<freeling::sentence> test_morfo_an();
}


#endif // WHOLE_H
