
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
#include <vector>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    class ImageEx final
    {
    public:
        /*!
        TODO : Documentation
        */
        struct Info final
        {
            Format format { Format::Unknown };
            int width { 0 };
            int height { 0 };
        };

    public:
        /*!
        TODO : Documentation
        */
        ImageEx();

        /*!
        TODO : Documentation
        */
        ImageEx(
            const Info& info,
            uint8_t* data = nullptr,
            bool managed = true
        );

    public:
        /*!
        TODO : Documentation
        */
        const Info& get_info() const;

        /*!
        TODO : Documentation
        */
        template <typename DataType = uint8_t>
        inline Span<const DataType> data() const
        {
            auto data = !mManagedData.empty() ? mManagedData.data() : nullptr;
            auto count = size_bytes() / sizeof(DataType);
            return Span<DataType>(reinterpret_cast<DataType*>(data), count);
        }

        /*!
        TODO : Documentation
        */
        template <typename DataType = uint8_t>
        inline Span<DataType> data()
        {
            auto data = !mManagedData.empty() ? mManagedData.data() : nullptr;
            auto count = size_bytes() / sizeof(DataType);
            return Span<DataType>(reinterpret_cast<DataType*>(data), count);
        }

#if 0
        /*!
        TODO : Documentation
        */
        template <typename T = uint8_t>
        inline Span<T> data() const
        {
            auto data = mUnmanagedData;
            if (!data) {
                data = !mManagedData.empty() ? mManagedData.data() : nullptr;
            }
            auto count = size_bytes() / sizeof(T);
            return Span<T>(reinterpret_cast<T*>(data), count);
        }

        template <typename PixelType = glm::u8vec4>
        inline const PixelType& get_pixel(glm::ivec2 xy)
        {
            xy.x = std::clamp<int>(xy.x, 0, mInfo.width);
            xy.y = std::clamp<int>(xy.y, 0, mInfo.height);
            return pixel[xy.y * mInfo.width + xy.x];
        }
#endif

        /*!
        TODO : Documentation
        */
        void resize(const Info& info);

        /*!
        TODO : Documentation
        */
        void clear();

        /*!
        TODO : Documentation
        */
        size_t size_bytes() const;

        /*!
        TODO : Documentation
        */
        void read_png(
            const dst::filesystem::path& filePath,
            Format format = Format::R8G8B8A8_Unorm
        );

        /*!
        TODO : Documentation
        */
        static void write_png(
            const ImageEx& image,
            const dst::filesystem::path& filePath
        );

    private:
        Info mInfo { };
        std::vector<uint8_t> mManagedData;
        uint8_t* mUnmanagedData { nullptr };
    };

} // namespace sys
} // namespace dst
