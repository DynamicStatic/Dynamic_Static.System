#if 0
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

namespace dst {
namespace sys {

    /*!
    TODO : Documentation.
    */
    struct Glyph final
    {
        static constexpr int InvalidId            { -1 };
        static constexpr int NullId               { 0 };    // &#00   U+0000
        static constexpr int LineFeedId           { 10 };   // &#10   U+000A
        static constexpr int SpaceId              { 32 };   // &#32   U+0020
        static constexpr int UnderscoreId         { 95 };   // &#95   U+005F
        static constexpr int LeftToRightId        { 8206 }; // &#8206 U+200E
        static constexpr int RightToLeftId        { 8207 }; // &#8207 U+200F
        static constexpr int LineSeperatorId      { 8232 }; // &#8232 U+
        static constexpr int ParagraphSeperatorId { 8233 }; // &#8233 U+
        static constexpr int NullInputId          { 9618 }; // &#9618 U+2592
        static constexpr const char* const LineFeed { "\n" };

        /*!
        TODO : Documentation.
        */
        struct Comparator final
        {
            /*!
            TODO : Documentation.
            */
            bool operator()(const Glyph& lhs, const Glyph& rhs) const;

            /*!
            TODO : Documentation.
            */
            bool operator()(const Glyph& lhs, const int& rhs) const;

            /*!
            TODO : Documentation.
            */
            bool operator()(const int& lhs, const Glyph& rhs) const;
        };

        int codepoint { };      //!< TODO : Documentation.
        float width { };        //!< TODO : Documentation.
        float height { };       //!< TODO : Documentation.
        float xOffset { };      //!< TODO : Documentation.
        float yOffset { };      //!< TODO : Documentation.
        float xAdvance { };     //!< TODO : Documentation.
        int page { };           //!< TODO : Documentation.
        int chnl { };           //!< TODO : Documentation.
        glm::vec2 texcoord { }; //!< TODO : Documentation.

        /*!
        TODO : Documentation.
        */
        bool is_printable() const;

        /*!
        TODO : Documentation.
        */
        static bool is_printable(int codepoint);
    };

} // namespace sys
} // namespace dst
#endif