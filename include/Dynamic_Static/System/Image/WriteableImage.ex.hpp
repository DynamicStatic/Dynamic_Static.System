#if 0
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/Image.hpp"

namespace dst {
namespace sys {

    /*!
    Provides high level control over writeable image data
    */
    class WriteableImage
        : public Image
    {
    public:
        /*!
        Destroys this instance of WriteableImage
        */
        inline virtual ~WriteableImage() = 0
        {
        }

    public:
        /*!
        Gets this WriteableImage's pixel data
        @param <PixelDataType = uint8_t> The type to interpret this WriteableImage's pixel data as
        @return This WriteableImage's pixel data
        */
        template <typename PixelDataType = uint8_t>
        inline Span<PixelDataType> pixel_data()
        {
            return { reinterpret_cast<PixelDataType*>(data()), size_bytes() / sizeof(PixelDataType) };
        }

        /*!
        Gets this WriteableImage's pixel at the given uv coordinate
        \n NOTE : uv coordinate (0, 0) returns the pixel at the top left corner of this WriteableImage
        @param <PixelDataType = uint8_t> The type to interpret this WriteableImage's pixel data as
        @param [in] uv The uv coordinate of the pixel to get
        */
        template <typename PixelDataType = uint8_t>
        inline PixelDataType& pixel_data(glm::ivec2 uv)
        {
            uv.x = std::clamp(uv.x, 0, get_info().width - 1);
            uv.y = std::clamp(uv.y, 0, get_info().height - 1);
            return pixel_data<PixelDataType>()[uv.y * get_info().width + uv.x];
        }

        /*!
        Gets this WriteableImage's data
        @return This WriteableImage's data
        */
        virtual uint8_t* data() = 0;
    };

} // namespace sys
} // namespace dst
#endif