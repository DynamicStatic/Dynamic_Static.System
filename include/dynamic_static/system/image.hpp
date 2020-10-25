
/*
==========================================
  Copyright (c) 2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/system/defines.hpp"

#include <filesystem>

namespace dst {
namespace sys {

/**
TODO : Documentation
*/
class Image final
{
public:
    /**
    TODO : Documentation
    */
    Image() = default;

    /**
    TODO : Documentation
    */
    uint32_t get_width() const;

    /**
    TODO : Documentation
    */
    uint32_t get_height() const;

    /**
    TODO : Documentation
    */
    size_t size_bytes() const;

    /**
    TODO : Documentation
    */
    const uint8_t* data() const;

    /**
    TODO : Documentation
    */
    void clear();

    /**
    TODO : Documentation
    */
    static void load(const std::filesystem::path& filePath, Image* pImage);

private:
    uint32_t mWidth { 0 };
    uint32_t mHeight { 0 };
    std::vector<uint8_t> mData;
};

} // namespace sys
} // namespace dst
