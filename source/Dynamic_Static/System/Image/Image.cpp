
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/Image.hpp"

namespace dst {
namespace sys {

    BasicImage::~BasicImage()
    {
    }

    BasicImage::BasicImage(const BasicImage& other)
    {
        *this = other;
    }

    BasicImage& BasicImage::operator=(const BasicImage& other)
    {
        mInfo = other.mInfo;
        return *this;
    }

    BasicImage::BasicImage(BasicImage&& other)
    {
        *this = std::move(other);
    }

    BasicImage& BasicImage::operator=(BasicImage&& other)
    {
        mInfo = std::move(other.mInfo);
        return *this;
    }

    const BasicImage::Info& BasicImage::get_info() const
    {
        return mInfo;
    }

    size_t BasicImage::size_bytes() const
    {
        return size_bytes(mInfo);
    }

    void BasicImage::clear()
    {
        mInfo = { };
    }

    size_t BasicImage::size_bytes(const Info& info)
    {
        auto bpp = get_format_bytes_per_pixel(info.format);
        return info.width * info.height * bpp;
    }

} // namespace sys
} // namespace dst
