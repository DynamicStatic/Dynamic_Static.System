
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <string>

namespace Dynamic_Static {
namespace System {

    /*
    * Represents a width and height.
    */
    struct Resolution final
    {
        /*
        * This Resolution's width
        */
        int width { 0 };

        /*
        * This Resolution's height
        */
        int height { 0 };

        /*
        * Gets this Resolution's aspect ratio.
        * @return This Resolution's aspect ratio
        */
        inline float get_aspect_ratio() const
        {
            auto w = static_cast<float>(width);
            auto h = static_cast<float>(height);
            return height ? w / h : 0;
        }

        /*
        * Gets this Resolution's std::string representation.
        * @return This Resolution's std::string representation
        */
        inline std::string to_string() const
        {
            return std::to_string(width) + " x " + std::to_string(height);
        }
    };

} // namespace System
} // namespace Dynamic_Static
