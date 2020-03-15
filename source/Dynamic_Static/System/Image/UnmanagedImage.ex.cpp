#if 0
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/UnmanagedImage.hpp"

namespace dst {
namespace sys {

    UnmanagedImage::UnmanagedImage(
        const Info& info,
        const void* data
    )
    {
        assign(info, data);
    }

    void UnmanagedImage::assign(
        const Info& info,
        const void* data
    )
    {
        if (data) {
            mInfo = info;
            mData = reinterpret_cast<const uint8_t*>(data);
        } else {
            clear();
        }
    }

    void UnmanagedImage::clear()
    {
        mData = nullptr;
        Image::clear();
    }

    const uint8_t* UnmanagedImage::data() const
    {
        return mData;
    }

} // namespace sys
} // namespace dst
#endif