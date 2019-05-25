
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image.hpp"

// #ifndef STB_IMAGE_IMPLEMENTATION
// #define STB_IMAGE_IMPLEMENTATION
// #endif
#include "stb_image.h"
// 
// #ifndef STB_IMAGE_WRITE_IMPLEMENTATION
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #endif
#include "stb_image_write.h"

#include <iostream>

namespace dst {
namespace sys {

    Image::Image(int width, int height, int depth)
        : mWidth { width }
        , mHeight { height }
        , mDepth { depth }
        , mData(mWidth * mHeight * mDepth)
    {
        // NOTE : This is creating a single channel Image.
        // TODO : Image should be templatized with PixelType.
    }

    uint8_t& Image::operator[](size_t index)
    {
        return mData[index];
    }

    uint8_t& Image::operator[](glm::ivec2 texCoord)
    {
        return mData[texCoord.y * mWidth + texCoord.x];
    }

    const uint8_t& Image::operator[](size_t index) const
    {
        return mData[index];
    }

    const uint8_t& Image::operator[](glm::ivec2 texCoord) const
    {
        assert(false && "TODO");
        return mData[0];
    }

    int Image::get_width() const
    {
        return mWidth;
    }

    int Image::get_height() const
    {
        return mHeight;
    }

    int Image::get_depth() const
    {
        return mDepth;
    }

    Span<uint8_t> Image::get_data()
    {
        return mData;
    }

    Span<const uint8_t> Image::get_data() const
    {
        return mData;
    }

    void Image::read_png(const StringView filePath)
    {
        mData.clear();
        int components = 0;
        auto image = stbi_load(filePath.data(), &mWidth, &mHeight, &components, STBI_rgb_alpha);
        if (image) {
            mDepth = 1;
            mData.resize(mWidth * mHeight * 4);
            memcpy(mData.data(), image, mData.size());
            stbi_image_free(image);
        } else {
            mWidth = 0;
            mHeight = 0;
            mDepth = 0;
            // TODO : Route to logger instead of std::cout
            std::cout << stbi_failure_reason() << std::endl;
        }
    }

    void Image::save_png(const StringView filePath) const
    {
        stbi_write_png(filePath.c_str(), mWidth, mHeight, 1, mData.data(), mWidth);
    }

} // namespace sys
} // namespace dst
