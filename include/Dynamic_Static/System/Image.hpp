
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#include <string_view>
#include <vector>

namespace Dynamic_Static {
namespace System {

    /*!
    Provides high level control over reading and writing images.
    */
    class Image final
    {
    private:
        int mWidth { 0 };
        int mHeight { 0 };
        int mDepth { 0 };
        std::vector<uint8_t> mData;

    public:
        /*!
        Gets this Image's width.
        @return This Image's width
        */
        int get_width() const;

        /*!
        Gets this Image's height.
        @return This Image's height
        */
        int get_height() const;

        /*!
        Gets this Image's depth.
        @return This Image's depth
        */
        int get_depth() const;

        /*!
        Gets this Image's data.
        @return This Image's data
        */
        dst::Span<uint8_t> get_data();

        /*!
        Gets this Image's data.
        @return This Image's data
        */
        dst::Span<const uint8_t> get_data() const;

        /*!
        Reads a .png file from a given file path.
        @param [in] filePath The file path of the .png to read
        */
        void read_png(dst::StringView filePath);
    };

} // namespace System
} // namespace Dynamic_Static
