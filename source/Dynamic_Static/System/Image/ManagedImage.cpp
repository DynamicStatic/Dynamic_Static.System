
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

    ManagedImage::ManagedImage(const ManagedImage& other)
    {
        *this = other;
    }

    ManagedImage& ManagedImage::operator=(const ManagedImage& other)
    {
        *this = static_cast<const BasicImage&>(other);
        BasicImage::operator=(other);
        return *this;
    }

    ManagedImage::ManagedImage(const BasicImage& other)
    {
        *this = other;
    }

    ManagedImage& ManagedImage::operator=(const BasicImage& other)
    {
        assign(other.get_info(), other.get_pixels().data());
        BasicImage::operator=(other);
        return *this;
    }

    ManagedImage::ManagedImage(ManagedImage&& other)
    {
        *this = std::move(other);
    }

    ManagedImage& ManagedImage::operator=(ManagedImage&& other)
    {
        mData = std::move(other.mData);
        BasicImage::operator=(std::move(other));
        return *this;
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

    void ManagedImage::clear()
    {
        mData.clear();
        BasicImage::clear();
    }

    void ManagedImage::resize(const Info& info)
    {
        mInfo = info;
        mData.resize(size_bytes(), 0);
    }

    bool ManagedImage::empty() const
    {
        return mData.empty();
    }

    const uint8_t* ManagedImage::data() const
    {
        return !mData.empty() ? mData.data() : nullptr;
    }

} // namespace sys
} // namespace dst
