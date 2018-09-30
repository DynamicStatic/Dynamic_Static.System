
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

namespace dst {
namespace sys {

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
        TODO : Documentation.
        */
        Image() = default;

        /*!
        TODO : Documentation.
        */
        Image(int width, int height = 1, int depth = 1);

        /*!
        Gets this Image's value at a given index.
        @return This Image's value at a given index
        */
        uint8_t& operator[](size_t index);

        /*!
        TODO : Documentation.
        */
        uint8_t& operator[](glm::ivec2 texCoord);

        /*!
        Gets this Image's value at a given index.
        @return This Image's value at a given index
        */
        const uint8_t& operator[](size_t index) const;

        /*!
        TODO : Documentation.
        */
        const uint8_t& operator[](glm::ivec2 texCoord) const;

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
        Span<uint8_t> get_data();

        /*!
        Gets this Image's data.
        @return This Image's data
        */
        Span<const uint8_t> get_data() const;

        /*!
        Reads a .png file from a given file path.
        @param [in] filePath The file path of the .png to read
        */
        void read_png(const StringView filePath);

        /*!
        TODO : Documentation.
        */
        void save_png(const StringView filePath) const;
    };

} // namespace sys
} // namespace dst
