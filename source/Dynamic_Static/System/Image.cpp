
/*
==========================================
  Copyright (c) 2018-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace dst {
namespace sys {

    uint8_t& Image::operator[](size_t index)
    {
        return mData[index];
    }
    const uint8_t& Image::operator[](size_t index) const
    {
        return mData[index];
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

    dst::Span<uint8_t> Image::get_data()
    {
        return mData;
    }

    dst::Span<const uint8_t> Image::get_data() const
    {
        return mData;
    }

    void Image::read_png(dst::StringView filePath)
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

} // namespace sys
} // namespace dst
