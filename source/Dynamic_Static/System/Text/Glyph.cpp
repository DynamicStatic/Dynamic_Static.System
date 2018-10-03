
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Text/Glyph.hpp"

namespace dst {
namespace sys {

    bool Glyph::Comparator::operator()(const Glyph& lhs, const Glyph& rhs) const
    {
        return lhs.codepoint < rhs.codepoint;
    }

    bool Glyph::Comparator::operator()(const Glyph& lhs, const int& rhs) const
    {
        return lhs.codepoint < rhs;
    }

    bool Glyph::Comparator::operator()(const int& lhs, const Glyph& rhs) const
    {
        return lhs < rhs.codepoint;
    }

    bool Glyph::is_printable() const
    {
        return is_printable(codepoint);
    }

    bool Glyph::is_printable(int codepoint)
    {
        bool printable = true;
        if (NullId <= codepoint && codepoint <= SpaceId) { // ASCII control characters
            printable = false;
        } else
        if (127 <= codepoint && codepoint <= 159) { // C1 extended control characters
            printable = false;
        } else
        if (codepoint == LeftToRightId ||
            codepoint == RightToLeftId ||
            codepoint == LineSeperatorId ||
            codepoint == ParagraphSeperatorId) {
            printable = false;
        }
        return printable;
    }

} // namespace sys
} // namespace dst
