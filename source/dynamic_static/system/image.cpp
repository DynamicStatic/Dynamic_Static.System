
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "dynamic_static/system/image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace dst {
namespace sys {

uint32_t Image::get_width() const
{
    return mWidth;
}

uint32_t Image::get_height() const
{
    return mHeight;
}

size_t Image::size_bytes() const
{
    return mData.size();
}

const uint8_t* Image::data() const
{
    return mData.data();
}

void Image::clear()
{
    *this = { };
}

void Image::load(const std::filesystem::path& filePath, Image* pImage)
{
    if (pImage) {
        pImage->clear();
        int width = 0;
        int height = 0;
        int components = 0;
        auto filePathStr = filePath.string();
        auto pixels = stbi_load(filePathStr.c_str(), &width, &height, &components, 4);
        pImage->mWidth = (uint32_t)width;
        pImage->mHeight = (uint32_t)height;
        pImage->mData.resize(width * height * 4);
        memcpy(pImage->mData.data(), pixels, pImage->mData.size());
        stbi_image_free(pixels);
    }
}

} // namespace sys
} // namespace dst
