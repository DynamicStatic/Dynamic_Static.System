
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
        R8_UNorm,
        R8G8_UNorm,
        R8G8B8_UNorm,
        R8G8B8A8_UNorm
    };

    /*!
    TODO : Documentation
    */
    int get_format_channel_count(Format format);

    /*!
    TODO : Documentation
    */
    int get_format_bytes_per_pixel(Format format);

    /*!
    TODO : Documentation
    */
    template <Format>
    struct Pixel final
    {
        typedef void type;
    };

    /*!
    TODO : Documentation
    */
    template <>
    struct Pixel<Format::R8_UNorm> final
    {
        typedef uint8_t type;
    };

    /*!
    TODO : Documentation
    */
    template <>
    struct Pixel<Format::R8G8_UNorm> final
    {
        typedef glm::u8vec2 type;
    };

    /*!
    TODO : Documentation
    */
    template <>
    struct Pixel<Format::R8G8B8_UNorm> final
    {
        typedef glm::u8vec3 type;
    };

    /*!
    TODO : Documentation
    */
    template <>
    struct Pixel<Format::R8G8B8A8_UNorm> final
    {
        typedef glm::u8vec4 type;
    };

} // namespace sys

    /*!
    Gets the std::string representation of a given Format
    @param [in] value The Format to get the std::string representation of
    @return The std::string representation of the given Format
    */
    std::string to_string(sys::Format format);

} // namespace dst
