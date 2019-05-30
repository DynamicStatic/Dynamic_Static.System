
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
    Provides high level control over managed image data
    */
    class ManagedImage final
        : public BasicImage
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
        inline ManagedImage(
            const Info& info,
            const uint8_t* data = nullptr
        )
        {
            assign(info, data);
        }

    public:
        /*!
        Assigns an Image::Info and optionaly pixel data to this ManagedImage
        @param [in] info This ManagedImage's Image::Info
        @param [in] data (optional = nullptr) A pointer to the data to copy to this ManagedImage
        \n NOTE : If data is not null it must point to a region of memory at least as large as the value returned by Image::size_bytes(info)
        */
        inline void assign(
            const Info& info,
            const uint8_t* data = nullptr
        )
        {
            resize(info);
            if (data) {
                memcpy(mData.data(), data, size_bytes());
            }
        }

        /*!
        Gets this ManagedImage's pixel data
        @param <PixelType = uint8_t> The type to interpret this ManagedImage's pixel data as
        @return This ManagedImage's pixel data
        */
        template <typename PixelType = uint8_t>
        inline Span<PixelType> get_pixels()
        {
            return { mData.data(), size_bytes() / sizeof(PixelType) };
        }

        /*!
        Gets this ManagedImage's pixel at the given uv coordinate
        \n NOTE : Uv coordinate (0, 0) returns the pixel at the top left corner of this ManagedImage
        @param <PixelType = uint8_t> The type to interpret this ManagedImage's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelType = uint8_t>
        inline PixelType& get_pixel(glm::ivec2 uv)
        {
            return const_cast<PixelType&>(BasicImage::get_pixel(uv));
        }

        /*!
        Clears this ManagedImage
        */
        inline void clear()
        {
            BasicImage::clear();
            mData.clear();
        }

        /*!
        Resizes this ManagedImage
        \n NOTE : Existing pixel data will be cleared
        */
        inline void resize(const Info& info)
        {
            mInfo = info;
            mData.resize(size_bytes(), 0);
        }

    private:
        inline const uint8_t* data() const
        {
            return !mData.empty() ? mData.data() : nullptr;
        }

        std::vector<uint8_t> mData;
    };

} // namespace sys
} // namespace dst
