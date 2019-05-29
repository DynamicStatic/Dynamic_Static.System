
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <string>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    enum class Format
    {
        Unknown,
        R8_Unorm,
        R8G8_Unorm,
        R8G8B8_Unorm,
        R8G8B8A8_Unorm
    };

    /*!
    TODO : Documentation
    */
    int get_format_channel_count(Format format);

    /*!
    TODO : Documentation
    */
    int get_format_bytes_per_pixel(Format format);

} // namespace sys

    /*!
    Gets the std::string representation of a given Format
    @param [in] value The Format to get the std::string representation of
    @return The std::string representation of the given Format
    */
    std::string to_string(sys::Format format);

} // namespace dst
