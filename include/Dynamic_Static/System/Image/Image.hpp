
/*
==========================================
  Copyright (c) 2018-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"
#include "Dynamic_Static/System/Format.hpp"

#include <algorithm>
#include <utility>

namespace dst {
namespace sys {

    /*!
    Provides high level control over image data
    */
    class BasicImage
    {
    public:
        /*!
        Provides configuration parameters for an Image
        */
        struct Info
        {
            Format format { Format::Unknown }; //!< The Image's Format
            int width { 0 };                   //!< The Image's width
            int height { 0 };                  //!< The Image's height
        };

    public:
        /*!
        Constructs an instance of Image
        */
        BasicImage() = default;

        /*!
        Destroys this instance of Image
        */
        virtual ~BasicImage() = 0;

    protected:
        /*!
        Constructs an instance of Image
        \n NOTE : Derived implementations must call Image::operator=()
        @param [in] other The Image to copy from
        */
        BasicImage(const BasicImage& other);

        /*!
        Constructs an instance of Image
        \n NOTE : Derived implementations must call Image::operator=()
        @param [in] other The Image to copy from
        @return This Image after being copied to
        */
        BasicImage& operator=(const BasicImage& other);

        /*!
        Moves an instance of Image
        \n NOTE : Derived implementations must call Image::operator=(&&)
        @param [in] other The Image to move from
        */
        BasicImage(BasicImage&& other);

        /*!
        Moves an instance of Image
        \n NOTE : Derived implementations must call Image::operator=(&&)
        @param [in] other The Image to move from
        @return This Image after being moved to
        */
        BasicImage& operator=(BasicImage&& other);

    public:
        /*!
        Gets this Image's Image::Info
        @return This Image's Image::Info
        */
        const Info& get_info() const;

        /*!
        Gets this Image's pixel data
        @param <PixelType = uint8_t> The type to interpret this Image's pixel data as
        @return This Image's pixel data
        */
        template <typename PixelType = uint8_t>
        inline Span<const PixelType> get_pixels() const
        {
            return { reinterpret_cast<const PixelType*>(data()), size_bytes() / sizeof(PixelType) };
        }

        /*!
        Gets this Image's pixel at the given uv coordinate
        \n NOTE : uv coordinate (0, 0) returns the pixel at the top left corner of this Image
        @param <PixelType = uint8_t> The type to interpret this Image's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelType = uint8_t>
        inline const PixelType& get_pixel(glm::ivec2 uv) const
        {
            uv.x = std::clamp(uv.x, 0, mInfo.width - 1);
            uv.y = std::clamp(uv.y, 0, mInfo.height - 1);
            return get_pixels<const PixelType>()[uv.y * mInfo.width + uv.x];
        }

        /*!
        Gets this Image's size in bytes
        @return This Image's size in bytes
        */
        size_t size_bytes() const;

        /*!
        Clears this Image
        \n NOTE : Derived implementations must call Image::clear()
        */
        virtual void clear() = 0;

        /*!
        Gets the size in bytes required for a given Image::Info
        @param [in] info The Image::Info to get the required size in bytes for
        @return This Image's size in bytes
        */
        static size_t size_bytes(const Info& info);

    protected:
        /*!
        Gets this Image's data
        @return This Image's data
        */
        virtual const uint8_t* data() const = 0;

        Info mInfo { }; //!< This Image's Image::Info
    };

    /*!
    Gets a value indicating whether or not the given Image::Infos are equal
    @param [in] lhs The left hand side Image::Info to compare
    @param [in] lhs The right hand side Image::Info to compare
    @return Whether or not the given Image::Infos are equal
    */
    bool operator==(
        const BasicImage::Info& lhs,
        const BasicImage::Info& rhs
    );

    /*!
    Gets a value indicating whether or not the given Image::Infos are inequal
    @param [in] lhs The left hand side Image::Info to compare
    @param [in] lhs The right hand side Image::Info to compare
    @return Whether or not the given Image::Infos are inequal
    */
    bool operator!=(
        const BasicImage::Info& lhs,
        const BasicImage::Info& rhs
    );

    /*!
    Gets a value indicating whether or not the given Images' contents are equal
    @param [in] lhs The left hand side Image to compare
    @param [in] lhs The right hand side Image to compare
    @return Whether or not the given Images' contents are equal
    */
    bool operator==(
        const BasicImage& lhs,
        const BasicImage& rhs
    );

    /*!
    Gets a value indicating whether or not the given Images' contents are inequal
    @param [in] lhs The left hand side Image to compare
    @param [in] lhs The right hand side Image to compare
    @return Whether or not the given Images' contents are inequal
    */
    bool operator!=(
        const BasicImage& lhs,
        const BasicImage& rhs
    );

} // namespace sys
} // namespace dst
