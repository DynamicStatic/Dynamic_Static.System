
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image.Ex.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include "stb_image_write.h"

#include <sstream>
#include <stdexcept>

namespace dst {
namespace sys {

    Image::Image(const Info& info)
    {
        resize(info);
    }

    const Image::Info& Image::get_info() const
    {
        return mInfo;
    }

    void Image::resize(const Image::Info& info)
    {
        mInfo = info;
        auto bpp = get_format_bytes_per_pixel(mInfo.format);
        mData.resize(mInfo.width * mInfo.height * mInfo.depth * bpp);
        if (mData.empty()) {
            clear();
        }
    }

    void Image::clear()
    {
        mInfo.format = Format::Unknown;
        mInfo.width = 0;
        mInfo.height = 0;
        mInfo.depth = 0;
        mData.clear();
    }

    void Image::read_png(
        const dst::filesystem::path& filePath,
        Format format
    )
    {
        mInfo.format = format;
        int requestedComponents = get_format_channel_count(mInfo.format);
        if (!requestedComponents) {
            mInfo.format = R8G8B8A8_Unorm;
            requestedComponents = get_format_channel_count(mInfo.format);
        }
        int components = 0;
        auto filePathStr = filePath.string();
        auto image = stbi_load(filePathStr.c_str(), &mInfo.width, &mInfo.height, &components, requestedComponents);
        if (image) {
            mInfo.depth = 1;
            resize(mInfo);
            memcpy(mData.data(), image, mData.size());
            stbi_image_free(image);
        } else {
            clear();
            std::stringstream strStr;
            strStr << "Failed to read png @ \"" << filePathStr << "\"" << " : " << stbi_failure_reason();
            throw std::runtime_error(strStr.str());
        }
    }

    void Image::write_png(const dst::filesystem::path& filePath)
    {

    }

} // namespace sys
} // namespace dst
