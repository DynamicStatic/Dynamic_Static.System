
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Image/BasicImage.hpp"

#include <type_traits>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    template <typename DataType = uint8_t>
    class UnmanagedImage final
        : public detail::BasicImage<UnmanagedImage<DataType>>
    {
    public:
        typedef detail::BasicImage<UnmanagedImage<DataType>> BasicImage;
        typedef typename BasicImage::Info Info;
        friend class BasicImage;

    public:
        /*!
        TODO : Documentation
        */
        UnmanagedImage() = default;

        /*!
        TODO : Documentation
        */
        inline UnmanagedImage(
            const Info& info,
            DataType* data
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
            DataType* data
        )
        {
            if (data) {
                mInfo = info;
                mData = data;
            } else {
                clear();
            }
        }

        /*!
        TODO : Documentation
        */
        inline void clear()
        {
            BasicImage::clear();
            mData = nullptr;
        }

    private:
        inline const uint8_t* getcdata() const
        {
            return mData;
        }

        // template <typename = typename std::enable_if<!std::is_const<DataType>::value>::type>
        inline uint8_t* getdata()
        {
            return mData;
        }

        DataType* mData { nullptr };

        static_assert(
            std::is_same<DataType, uint8_t>::value ||
            std::is_same<DataType, const uint8_t>::value,
            "UnmanagedImage DataType must be uint8_t or const uint8_t"
        );
    };

} // namespace sys
} // namespace dst
