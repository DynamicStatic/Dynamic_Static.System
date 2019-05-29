
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
            case Format::R8_Unorm: return 1;
            case Format::R8G8_Unorm: return 2;
            case Format::R8G8B8_Unorm: return 3;
            case Format::R8G8B8A8_Unorm: return 4;
            case Format::Unknown:
            default: return 0;
        }
    }

    int get_format_bytes_per_pixel(Format format)
    {
        switch (format) {
            case Format::R8_Unorm: return 1;
            case Format::R8G8_Unorm: return 2;
            case Format::R8G8B8_Unorm: return 3;
            case Format::R8G8B8A8_Unorm: return 4;
            case Format::Unknown:
            default: return 0;
        }
    }

} // namespace sys

    std::string to_string(sys::Format format)
    {
        using namespace sys;
        switch (format) {
            case Format::R8_Unorm: return       "R8_Unorm";
            case Format::R8G8_Unorm: return     "R8G8_Unorm";
            case Format::R8G8B8_Unorm: return   "R8G8B8_Unorm";
            case Format::R8G8B8A8_Unorm: return "R8G8B8A8_Unorm";
            case Format::Unknown:
            default: return "Unkown";
        }
    }

} // namespace dst
