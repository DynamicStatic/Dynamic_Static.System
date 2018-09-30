
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

    bool Glyph::is_printable() const
    {
        bool printable = true;
        // ASCII control characters
        if (NullId <= id && id <= SpaceId) {
            printable = false;
        } else
        // C1 extended control characters
        if (127 <= id && id <= 159) {
            printable = false;
        } else
        if (id == LeftToRightId ||
            id == RightToLeftId ||
            id == LineSeperatorId ||
            id == ParagraphSeperatorId) {
            printable = false;
        }
        return printable;
    }

} // namespace sys
} // namespace dst
