
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Image/Image.hpp"
#include "Dynamic_Static/System/Defines.hpp"

namespace dst {
namespace sys {

    /*!
    Provides high level control over unmanaged read only image data
    */
    class UnmanagedImage
        : public Image
    {
    public:
        /*!
        Constructs an instance of UnmanagedImage
        */
        UnmanagedImage() = default;

        /*!
        Constructs an instance of UnmanagedImage
        @param [in] info This UnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this UnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this UnmanagedImage will be cleared
        */
        UnmanagedImage(
            const Info& info,
            const void* data
        );

    public:
        /*!
        Assigns an Image::Info and pixel data to this UnmanagedImage
        @param [in] info This UnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this UnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this UnmanagedImage will be cleared
        */
        void assign(
            const Info& info,
            const void* data
        );

        /*!
        Clears this UnmanagedImage
        */
        void clear() override final;

        /*!
        Gets this UnmanagedImage's data
        @return This UnmanagedImage's data
        */
        const uint8_t* data() const override final;

    private:
        const uint8_t* mData;
    };

} // namespace sys
} // namespace dst
