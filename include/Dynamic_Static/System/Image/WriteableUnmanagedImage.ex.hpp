#if 0
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Image/WriteableImage.hpp"
#include "Dynamic_Static/System/Defines.hpp"

#include <type_traits>

namespace dst {
namespace sys {

    /*!
    Provides high level control over unmanaged image data
    */
    class WriteableUnmanagedImage
        : public WriteableImage
    {
    public:
        /*!
        Constructs an instance of WriteableUnmanagedImage
        */
        WriteableUnmanagedImage() = default;

        /*!
        Constructs an instance of WriteableUnmanagedImage
        @param [in] info This WriteableUnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this WriteableUnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this WriteableUnmanagedImage will be cleared
        */
        WriteableUnmanagedImage(
            const Info& info,
            void* data
        );

    public:
        /*!
        Assigns an Image::Info and pixel data to this WriteableUnmanagedImage
        @param [in] info This WriteableUnmanagedImage's Image::Info
        @param [in] data A pointer to the data to access via this WriteableUnmanagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        \n NOTE : If data is null this WriteableUnmanagedImage will be cleared
        */
        void assign(
            const Info& info,
            void* data
        );

        /*!
        Clears this WriteableUnmanagedImage
        */
        void clear() override final;

        /*!
        Gets this WriteableUnmanagedImage's data
        @return This WriteableUnmanagedImage's data
        */
        uint8_t* data() override final;

    private:
        uint8_t* mData;
    };

} // namespace sys
} // namespace dst
#endif