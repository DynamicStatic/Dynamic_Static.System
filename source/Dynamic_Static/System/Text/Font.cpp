
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Text/Font.hpp"

#ifndef STB_TRUETYPE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#endif
#include "stb_truetype.h"

#include <fstream>

namespace dst {
namespace sys {

    void Font::read_ttf(dst::StringView filePath)
    {
        std::ifstream fontFile(filePath.data(), std::ios::binary);
    }

} // namespace sys
} // namespace dst
