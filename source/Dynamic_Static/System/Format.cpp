
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Format.hpp"

namespace dst {
namespace sys {

    int get_format_channel_count(Format format)
    {
        switch (format) {
            case R8_Unorm: return 1;
            case R8G8_Unorm: return 2;
            case R8G8B8_Unorm: return 3;
            case R8G8B8A8_Unorm: return 4;
            case Unknown:
            default: return 0;
        }
    }

    int get_format_bytes_per_pixel(Format format)
    {
        switch (format) {
            case R8_Unorm: return 1;
            case R8G8_Unorm: return 2;
            case R8G8B8_Unorm: return 3;
            case R8G8B8A8_Unorm: return 4;
            case Unknown:
            default: return 0;
        }
    }

} // namespace sys
} // namespace dst
