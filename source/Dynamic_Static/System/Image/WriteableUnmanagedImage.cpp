
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/WriteableUnmanagedImage.hpp"

namespace dst {
namespace sys {

    WriteableUnmanagedImage::WriteableUnmanagedImage(
        const Info& info,
        void* data
    )
    {
        assign(info, data);
    }

    void WriteableUnmanagedImage::assign(
        const Info& info,
        void* data
    )
    {
        if (data) {
            mInfo = info;
            mData = reinterpret_cast<uint8_t*>(data);
        } else {
            clear();
        }
    }

    void WriteableUnmanagedImage::clear()
    {
        mData = nullptr;
        Image::clear();
    }

    uint8_t* WriteableUnmanagedImage::data()
    {
        return mData;
    }

} // namespace sys
} // namespace dst
