
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Text/Glyph.hpp"
#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Image.hpp"

#include <map>
#include <unordered_map>
#include <utility>

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
        float mAscent { };
        float mDescent { };
        float mLineHeight { };
        float mBaseline { };
        Glyph mNullGlyph { };
        std::vector<Glyph> mGlyphs;
        std::map<std::pair<int, int>, float> mKerningPairs;
        Image mImage;

    public:
        /*!
        TODO : Documentation.
        */
        const Glyph& operator[](int codepoint) const;

    public:
        /*!
        TODO : Documentation.
        */
        float get_ascent() const;

        /*!
        TODO : Documentation.
        */
        float get_descent() const;

        /*!
        TODO : Documentation.
        */
        float get_line_height() const;

        /*!
        TODO : Documentation.
        */
        float get_baseline() const;

        /*!
        TODO : Documentation.
        */
        const Image& get_image() const;

        /*!
        TODO : Documentation.
        */
        float get_kerning(int codepoint0, int codepoint1) const;

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
