#if 0
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/Image.hpp"

#include <utility>

namespace dst {
namespace sys {

    Image::~Image()
    {
    }

    const Image::Info& Image::get_info() const
    {
        return mInfo;
    }

    void Image::clear()
    {
        mInfo = { };
    }

    bool Image::empty() const
    {
        return !size_bytes();
    }

    size_t Image::size_bytes() const
    {
        return size_bytes(mInfo);
    }

    size_t Image::size_bytes(const Info& info)
    {
        auto bpp = get_format_bytes_per_pixel(info.format);
        return info.width * info.height * bpp;
    }

    bool operator==(const Image::Info& lhs, const Image::Info& rhs)
    {
        return
            lhs.format == rhs.format &&
            lhs.width == rhs.width &&
            lhs.height == rhs.height;
    }

    bool operator!=(const Image::Info& lhs, const Image::Info& rhs)
    {
        return !(lhs == rhs);
    }

    bool operator==(const Image& lhs, const Image& rhs)
    {
        return lhs.get_info() == rhs.get_info() && !memcmp(lhs.data(), rhs.data(), lhs.size_bytes());
    }

    bool operator!=(const Image& lhs, const Image& rhs)
    {
        return !(lhs == rhs);
    }

} // namespace sys
} // namespace dst
#endif