
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

    bool operator==(
        const BasicImage::Info& lhs,
        const BasicImage::Info& rhs
    )
    {
        return
            lhs.format == rhs.format &&
            lhs.width == rhs.width &&
            lhs.height == rhs.height;
    }

    bool operator!=(
        const BasicImage::Info& lhs,
        const BasicImage::Info& rhs
    )
    {
        return !(lhs == rhs);
    }

    bool operator==(
        const BasicImage& lhs,
        const BasicImage& rhs
    )
    {
        return
            lhs.get_info() == rhs.get_info() &&
            !memcmp(lhs.get_pixels().data(), rhs.get_pixels().data(), BasicImage::size_bytes(lhs.get_info()));
    }

    bool operator!=(
        const BasicImage& lhs,
        const BasicImage& rhs
    )
    {
        return !(lhs == rhs);
    }

} // namespace sys
} // namespace dst
