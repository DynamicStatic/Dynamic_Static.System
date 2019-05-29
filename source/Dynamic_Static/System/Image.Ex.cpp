
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/
#if 0
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
#include <utility>

namespace dst {
namespace sys {

    const ImageEx::Info& ImageEx::get_info() const
    {
        return mInfo;
    }

    void ImageEx::resize(const ImageEx::Info& info)
    {
        mInfo = info;
        mManagedData.clear();
        mManagedData.resize(size_bytes());
    }

    void ImageEx::clear()
    {
#if 0
        mInfo.format = Format::Unknown;
        mInfo.width = 0;
        mInfo.height = 0;
        mInfo.managed = false;
        mManagedData.clear();
        mUnmanagedData = nullptr;
#endif
    }

    size_t ImageEx::size_bytes() const
    {
        auto bpp = get_format_bytes_per_pixel(mInfo.format);
        return mInfo.width * mInfo.height * bpp;
    }

    void ImageEx::read_png(
        const dst::filesystem::path& filePath,
        Format format
    )
    {
        mInfo.format = format;
        int requestedComponents = get_format_channel_count(mInfo.format);
        if (!requestedComponents) {
            mInfo.format = Format::R8G8B8A8_Unorm;
            requestedComponents = get_format_channel_count(mInfo.format);
        }
        int components = 0;
        auto filePathStr = filePath.string();
        auto image = stbi_load(filePathStr.c_str(), &mInfo.width, &mInfo.height, &components, requestedComponents);
        if (image) {
            resize(mInfo);
            memcpy(mManagedData.data(), image, mManagedData.size());
            stbi_image_free(image);
        } else {
            clear();
            std::stringstream strStr;
            strStr << "Failed to read png @ \"" << filePath << "\"" << " : " << stbi_failure_reason();
            throw std::runtime_error(strStr.str());
        }
    }

    void ImageEx::write_png(
        const ImageEx& image,
        const dst::filesystem::path& filePath
    )
    {
        if (!image.size_bytes()) {
            std::stringstream strStr;
            strStr << "Failed to write png @ \"" << filePath << "\"" << " : no data";
            throw std::runtime_error(strStr.str());
        }
        auto const& imageInfo = image.get_info();
        auto components = get_format_channel_count(imageInfo.format);
        auto stride = imageInfo.width * get_format_bytes_per_pixel(imageInfo.format);
        if (!components || !stride) {
            std::stringstream strStr;
            strStr << "Failed to write png @ \"" << filePath << "\"" << " : unsupported Format::" << to_string(imageInfo.format) << "";
            throw std::runtime_error(strStr.str());
        }
        auto filePathStr = filePath.string();
        auto error = stbi_write_png(filePathStr.c_str(), imageInfo.width, imageInfo.height, components, nullptr, stride);
        if (error) {
            std::stringstream strStr;
            strStr << "Failed to write png @ \"" << filePath << "\" : stbi_write_png() failed";
            throw std::runtime_error(strStr.str());
        }
    }

} // namespace sys
} // namespace dst
#endif
