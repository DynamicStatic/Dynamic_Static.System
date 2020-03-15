#if 0
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/ManagedImage.hpp"

namespace dst {
namespace sys {

    ManagedImage::ManagedImage(
        const Info& info,
        const void* data
    )
    {
        assign(info, data);
    }

    const uint8_t* ManagedImage::data() const
    {
        return !mData.empty() ? mData.data() : nullptr;
    }

    uint8_t* ManagedImage::data()
    {
        return !mData.empty() ? mData.data() : nullptr;
    }

    void ManagedImage::assign(
        const Info& info,
        const void* data
    )
    {
        resize(info);
        if (data) {
            memcpy(mData.data(), data, size_bytes());
        }
    }

    void ManagedImage::resize(const Info& info)
    {
        mInfo = info;
        mData.resize(size_bytes(), 0);
    }

    void ManagedImage::clear()
    {
        mData.clear();
        Image::clear();
    }

} // namespace sys
} // namespace dst
#endif