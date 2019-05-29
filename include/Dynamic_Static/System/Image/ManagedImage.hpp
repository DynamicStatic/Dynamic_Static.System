
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Image/BasicImage.hpp"

#include <vector>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    class ManagedImage final
        : public detail::BasicImage<ManagedImage>
    {
    public:
        typedef detail::BasicImage<ManagedImage> BasicImage;
        typedef typename BasicImage::Info Info;
        friend class BasicImage;

    public:
        /*!
        TODO : Documentation
        */
        ManagedImage() = default;

        /*!
        TODO : Documentation
        */
        inline ManagedImage(
            const Info& info,
            const uint8_t* data = nullptr
        )
        {
            assign(info, data);
        }

    public:
        /*!
        TODO : Documentation
        */
        inline void assign(
            const Info& info,
            const uint8_t* data
        )
        {
            resize(info);
            if (data) {
                memcpy(mData.data(), data, size_bytes());
            }
        }

        /*!
        TODO : Documentation
        */
        inline void resize(const Info& info)
        {
            mInfo = info;
            mData.resize(size_bytes(), 0);
        }

        /*!
        TODO : Documentation
        */
        inline void clear()
        {
            BasicImage::clear();
            mData.clear();
        }

    private:
        inline const uint8_t* getcdata() const
        {
            return !mData.empty() ? mData.data() : nullptr;
        }

        inline uint8_t* getdata()
        {
            return !mData.empty() ? mData.data() : nullptr;
        }

        std::vector<uint8_t> mData;
    };

} // namespace sys
} // namespace dst
