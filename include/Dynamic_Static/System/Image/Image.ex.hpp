#if 0
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

namespace dst {
namespace sys {

    /*!
    Provides high level control over image data
    */
    class Image
    {
    public:
        /*!
        Provides configuration parameters for an Image
        */
        struct Info
        {
            Format format { Format::Unknown }; //!< The configured Image's Format
            int width { 0 };                   //!< The configured Image's width in pixels
            int height { 0 };                  //!< The configured Image's height in pixels
        };

    public:
        /*!
        Constructs an instance of Image
        */
        Image() = default;

        /*!
        Destroys this instance of Image
        */
        virtual ~Image() = 0;

    public:
        /*!
        Gets this Image's Image::Info
        @return This Image's Image::Info
        */
        const Info& get_info() const;

        /*!
        Gets this Image's pixel data
        @param <PixelDataType = uint8_t> The type to interpret this Image's pixel data as
        @return This Image's pixel data
        */
        template <typename PixelDataType = uint8_t>
        inline Span<const PixelDataType> pixel_data() const
        {
            return { reinterpret_cast<const PixelDataType*>(data()), size_bytes() / sizeof(PixelDataType) };
        }

        /*!
        Gets this Image's pixel at the given uv coordinate
        \n NOTE : uv coordinate (0, 0) returns the pixel at the top left corner of this Image
        @param <PixelDataType = uint8_t> The type to interpret this Image's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelDataType = uint8_t>
        inline const PixelDataType& pixel_data(glm::ivec2 uv) const
        {
            uv.x = std::clamp(uv.x, 0, get_info().width - 1);
            uv.y = std::clamp(uv.y, 0, get_info().height - 1);
            return pixel_data<const PixelDataType>()[uv.y * get_info().width + uv.x];
        }

        /*!
        Gets this Image's data
        @return This Image's data
        */
        virtual const uint8_t* data() const = 0;

        /*!
        Gets a value indicating whether or not this Image is empty
        @return Whether or not this Image is empty
        */
        bool empty() const;

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
        Info mInfo { };

    private:
        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;
        Image(Image&&) = delete;
        Image& operator=(Image&&) = delete;
    };

    /*!
    Gets a value indicating whether or not the given Image::Infos are equal
    @param [in] lhs The left hand side Image::Info to compare
    @param [in] lhs The right hand side Image::Info to compare
    @return Whether or not the given Image::Infos are equal
    */
    bool operator==(const Image::Info& lhs, const Image::Info& rhs);

    /*!
    Gets a value indicating whether or not the given Image::Infos are inequal
    @param [in] lhs The left hand side Image::Info to compare
    @param [in] lhs The right hand side Image::Info to compare
    @return Whether or not the given Image::Infos are inequal
    */
    bool operator!=(const Image::Info& lhs, const Image::Info& rhs);

    /*!
    Gets a value indicating whether or not the given Images' contents are equal
    @param [in] lhs The left hand side Image to compare
    @param [in] lhs The right hand side Image to compare
    @return Whether or not the given Images' contents are equal
    */
    bool operator==(const Image& lhs, const Image& rhs);

    /*!
    Gets a value indicating whether or not the given Images' contents are inequal
    @param [in] lhs The left hand side Image to compare
    @param [in] lhs The right hand side Image to compare
    @return Whether or not the given Images' contents are inequal
    */
    bool operator!=(const Image& lhs, const Image& rhs);

} // namespace sys
} // namespace dst
#endif