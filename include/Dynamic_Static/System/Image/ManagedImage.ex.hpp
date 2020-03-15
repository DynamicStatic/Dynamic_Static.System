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

#include <vector>

namespace dst {
namespace sys {

    /*!
    Provides high level control over managed image data
    */
    class ManagedImage final
        : public WriteableImage
    {
    public:
        /*!
        Constructs an instance of ManagedImage
        */
        ManagedImage() = default;

        /*!
        Constructs an instance of ManagedImage
        @param [in] info This ManagedImage's Image::Info
        @param [in] data (optional = nullptr) A pointer to the data to copy to this ManagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        */
        ManagedImage(
            const Info& info,
            const void* data = nullptr
        );

    public:
        /*!
        Assigns an Image::Info and optionaly pixel data to this ManagedImage
        @param [in] info This ManagedImage's Image::Info
        @param [in] data (optional = nullptr) A pointer to the data to copy to this ManagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        */
        void assign(
            const Info& info,
            const void* data = nullptr
        );

        /*!
        Gets this ManagedImage's data
        @return This ManagedImage's data
        */
        const uint8_t* data() const override final;

        /*!
        Gets this ManagedImage's data
        @return This ManagedImage's data
        */
        uint8_t* data() override final;

        /*!
        Clears this ManagedImage
        */
        void clear() override final;

        /*!
        Resizes this ManagedImage
        \n NOTE : This method clears existing pixel data
        */
        void resize(const Info& info);

    private:
        std::vector<uint8_t> mData;
    };

} // namespace sys
} // namespace dst
#endif