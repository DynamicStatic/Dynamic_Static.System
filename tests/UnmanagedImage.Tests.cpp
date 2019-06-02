
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/UnmanagedImage.hpp"

#include "catch.hpp"

#include <algorithm>
#include <vector>

namespace dst {
namespace sys {
namespace tests {

    TEST_CASE("Default UnmanagedImage<>::ctor() zeros out all fields", "[UnmanagedImage]")
    {
        UnmanagedImage image;
        CHECK(image.get_info().format == Format::Unknown);
        CHECK(image.get_info().width == 0);
        CHECK(image.get_info().height == 0);
        CHECK(image.empty());
    }

    TEST_CASE("Passing nullptr to UnmanagedImage<>::ctor() zeros out all fields", "[UnmanagedImage]")
    {
        BasicImage::Info imageInfo { };
        imageInfo.format = Format::R8G8B8A8_UNorm;
        imageInfo.width = 16;
        imageInfo.height = 16;
        UnmanagedImage image(imageInfo, nullptr);
        CHECK(image.get_info().format == Format::Unknown);
        CHECK(image.get_info().width == 0);
        CHECK(image.get_info().height == 0);
        CHECK(image.empty());
    }

    TEST_CASE("UnmanagedImage<ReadOnly>::ctor() correctly sets all fields", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range<uint8_t>(0, 255);
            }
        }

        BasicImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        UnmanagedImage<ReadOnly> image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size());
        CHECK(image.get_pixels().data() == data.data());
    }

    TEST_CASE("UnmanagedImage<Mutable> read / write individual pixels", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range<uint8_t>(0, 255);
            }
        }

        BasicImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        UnmanagedImage<Mutable> image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size());
        CHECK(image.get_pixels().data() == data.data());
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                image.get_pixel({ x, y }) = 128;
            }
        }
        auto predicate = [](uint8_t value) { return value == 128; };
        CHECK(std::all_of(data.begin(), data.end(), predicate));
    }

    TEST_CASE("UnmanagedImage<>::clear() works correctly", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8G8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = {
                    rng.range(0, 255),
                    rng.range(0, 255)
                };
            }
        }

        BasicImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        UnmanagedImage image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size() * sizeof(data[0]));
        image.clear();
        CHECK(image.empty());
    }

    TEST_CASE("UnmanagedImage<> comparison operators work correctly", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8G8B8_UNorm;
        std::vector<Pixel<format>::type> data0(width * height);
        std::vector<Pixel<format>::type> data1(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto index = y * width + x;
                Pixel<format>::type pixel {
                    rng.range(0, 255),
                    rng.range(0, 255),
                    rng.range(0, 255)
                };
                data0[index] = pixel;
                data1[index] = pixel;
            }
        }

        BasicImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        UnmanagedImage<ReadOnly> image0(imageInfo, data0.data());
        UnmanagedImage<Mutable> image1(imageInfo, data1.data());
        CHECK(image0 == image1);
        for (auto& pixel : image1.get_pixels<Pixel<format>::type>()) {
            pixel.r = rng.range<uint8_t>(0, 255);
            pixel.g = rng.range<uint8_t>(0, 255);
            pixel.b = rng.range<uint8_t>(0, 255);
        }
        CHECK(image0 != image1);
    }

#if 0
    TEST_CASE("Assignment operator works correctly", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8G8B8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = {
                    rng.range(0, 255),
                    rng.range(0, 255),
                    rng.range(0, 255)
                };
            }
        }

        ManagedImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image0(imageInfo, data.data());
        auto image1 = image0;
        CHECK(image0 == image1);
        image1.clear();
        CHECK(image0 != image1);
    }

    TEST_CASE("Assignment operator from UnmanagedImage works correctly", "[UnmanagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8G8B8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = {
                    rng.range(0, 255),
                    rng.range(0, 255),
                    rng.range(0, 255)
                };
            }
        }

        ManagedImage::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        UnmanagedImage image0(imageInfo, (uint8_t*)data.data());
        ManagedImage image1 = image0;
        CHECK(image0 == image1);
        image0.clear();
        CHECK(image0 != image1);
    }
    #endif

} // namespace tests
} // namespace sys
} // namespace dst
