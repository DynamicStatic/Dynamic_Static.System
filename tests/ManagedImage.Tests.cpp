
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#if 0
#include "Dynamic_Static/System/Image/ManagedImage.hpp"

#include "catch.hpp"

#include <vector>

namespace dst {
namespace sys {
namespace tests {

    TEST_CASE("Default ctor() zeros out all info fields", "[ManagedImage]")
    {
        ManagedImage image;
        CHECK(image.get_info().format == Format::Unknown);
        CHECK(image.get_info().width == 0);
        CHECK(image.get_info().height == 0);
    }

    TEST_CASE("ManagedImage storage is correctly allocated", "[ManagedImage]")
    {
        ManagedImage::Info imageInfo { };
        imageInfo.format = Format::R8G8B8A8_Unorm;
        imageInfo.width = 16;
        imageInfo.height = 16;
        ManagedImage image(imageInfo);
        CHECK(image.get_info().format == Format::R8G8B8A8_Unorm);
        CHECK(image.get_info().width == 16);
        CHECK(image.get_info().height == 16);
        auto sizeBytes = imageInfo.width * imageInfo.height * get_format_bytes_per_pixel(imageInfo.format);
        CHECK(image.size_bytes() == sizeBytes);
    }

    TEST_CASE("ManagedImage can read / write pixels", "[ManagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        std::vector<uint8_t> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range<uint8_t>(0, 255);
            }
        }

        ManagedImage::Info imageInfo { };
        imageInfo.format = Format::R8_Unorm;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo);
        REQUIRE(image.size_bytes() == data.size());
        memcpy(image.get_pixels().data(), data.data(), image.size_bytes());
        CHECK(!memcmp(image.get_pixels().data(), data.data(), image.size_bytes()));
    }

    TEST_CASE("ManagedImage can read / write individual pixels", "[ManagedImage]")
    {
        uint8_t uydata;
        BasicImage::Info info { };
        UnmanagedImage<const uint8_t> ui(info, &uydata);
        auto r = ui.get_pixel({ 0,0 });
        // ui.get_pixel({ 0, 0 }) = (uint8_t)0;
        (void)r;

        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        std::vector<uint8_t> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range<uint8_t>(0, 255);
            }
        }

        ManagedImage::Info imageInfo { };
        imageInfo.format = Format::R8_Unorm;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo);
        REQUIRE(image.size_bytes() == data.size());
        memcpy(image.get_pixels().data(), data.data(), image.size_bytes());
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto index = y * width + x;
                CHECK(image.get_pixel({ x, y }) == data[index]);
                auto value = rng.range<uint8_t>(0, 255);
                image.get_pixel({ x, y }) = value;
                data[index] = value;
            }
        }
        CHECK(!memcmp(image.get_pixels().data(), data.data(), image.size_bytes()));
    }

    TEST_CASE("ManagedImage ctor() copies data correctly", "[ManagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        std::vector<uint8_t> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range<uint8_t>(0, 255);
            }
        }

        ManagedImage::Info imageInfo { };
        imageInfo.format = Format::R8_Unorm;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size());
        CHECK(!memcmp(image.get_pixels().data(), data.data(), image.size_bytes()));
    }

} // namespace tests
} // namespace sys
} // namespace dst
#endif
