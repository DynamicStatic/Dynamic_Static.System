
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Text/Glyph.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Image.hpp"

#include <unordered_map>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation.
    */
    class Font final
    {
    public:
        static constexpr const char* const DefaultCharacterSet {
            "`~!@#$%^&*()-=_+[]\\{}|;':\",./<>? "
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789"
        };

    private:
        float mAscent { 0 };
        float mDescent { 0 };
        float mLineGap { 0 };
        std::unordered_map<int, Glyph> mGlyphs;
        Image mImage;

    public:
        float get_ascent() const;
        float get_descent() const;
        float get_line_gap() const;
        const Image& get_image() const;

        /*!
        TODO : Documentation.
        */
        void read_ttf(
            const dst::StringView filePath,
            float lineHeight,
            const dst::StringView characters = DefaultCharacterSet
        );
    };

} // namespace sys
} // namespace dst
