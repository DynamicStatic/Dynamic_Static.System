
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

#include <vector>

namespace dst {
namespace sys {

    /*!
    TODO : Documentation
    */
    class Image final
    {
    public:
        /*!
        TODO : Documentation
        */
        struct Info final
        {
            Format format { Unknown };
            int width { 1 };
            int height { 1 };
            int depth { 1 };
        };

    public:
        /*!
        TODO : Documentation
        */
        Image() = default;

        /*!
        TODO : Documentation
        */
        Image(const Info& info);

    public:
        /*!
        TODO : Documentation
        */
        const Info& get_info() const;

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
        void read_png(
            const dst::filesystem::path& filePath,
            Format format = R8G8B8A8_Unorm
        );

        /*!
        TODO : Documentation
        */
        void write_png(const dst::filesystem::path& filePath);

    private:
        Info mInfo { };
        std::vector<uint8_t> mData;
    };

} // namespace sys
} // namespace dst
