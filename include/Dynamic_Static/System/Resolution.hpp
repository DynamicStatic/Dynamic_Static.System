
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/Core/Defines.hpp"

#include <string>

namespace Dynamic_Static {
namespace System {

    /**
     * Represents a width and height.
     */
    struct Resolution final
    {
    public:
        uint32_t width { 0 };  /*!< TODO : Documentation. */
        uint32_t height { 0 }; /*!< TODO : Documentation. */

    public:
        /**
         * Gets this Resolution's aspect ratio.
         * @return This Resolution's aspect ratio
         */
        float get_aspect_ratio() const;

        /**
         * Gets this Resolution's std::string representation.
         * @return This Resolution's std::string representation
         */
        std::string to_string() const;
    };

} // namespace System
} // namespace Dynamic_Static
