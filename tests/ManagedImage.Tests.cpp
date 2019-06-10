
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image/ManagedImage.hpp"

#include "catch.hpp"

#include <vector>

namespace dst {
namespace sys {
namespace tests {

    TEST_CASE("Default ManagedImage::ctor() zeros out all fields", "[ManagedImage]")
    {
        ManagedImage image;
        CHECK(image.get_info().format == Format::Unknown);
        CHECK(image.get_info().width == 0);
        CHECK(image.get_info().height == 0);
        CHECK(image.pixel_data().empty());
        CHECK(image.size_bytes() == 0);
        CHECK(image.data() == nullptr);
        CHECK(image.empty());
    }

    TEST_CASE("ManagedImage storage is correctly allocated", "[ManagedImage]")
    {
        Image::Info imageInfo { };
        imageInfo.format = Format::R8G8B8A8_UNorm;
        imageInfo.width = 16;
        imageInfo.height = 32;
        ManagedImage image(imageInfo);
        CHECK(image.get_info().format == imageInfo.format);
        CHECK(image.get_info().width == imageInfo.width);
        CHECK(image.get_info().height == imageInfo.height);
        auto sizeBytes = imageInfo.width * imageInfo.height * get_format_bytes_per_pixel(imageInfo.format);
        CHECK(image.size_bytes() == sizeBytes);
    }

    TEST_CASE("ManagedImage read / write pixels", "[ManagedImage]")
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

        Image::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo);
        REQUIRE(image.size_bytes() == data.size());
        memcpy(image.data(), data.data(), image.size_bytes());
        CHECK(!memcmp(image.data(), data.data(), image.size_bytes()));
    }

    TEST_CASE("ManagedImage read / write individual pixels", "[ManagedImage]")
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

        Image::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo);
        REQUIRE(image.size_bytes() == data.size());
        memcpy(image.data(), data.data(), image.size_bytes());
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                auto index = y * width + x;
                if (image.pixel_data({ x, y }) != data[index]) {
                    CHECK(image.pixel_data({ x, y }) == data[index]);
                    break;
                }
                auto value = rng.range<uint8_t>(0, 255);
                image.pixel_data({ x, y }) = value;
                data[index] = value;
            }
        }
        CHECK(!memcmp(image.data(), data.data(), image.size_bytes()));
    }

    TEST_CASE("ManagedImage::ctor() copies data correctly", "[ManagedImage]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        constexpr auto format = Format::R8G8B8A8_UNorm;
        std::vector<Pixel<format>::type> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = {
                    rng.range(0, 255),
                    rng.range(0, 255),
                    rng.range(0, 255),
                    rng.range(0, 255)
                };
            }
        }

        Image::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size() * sizeof(data[0]));
        CHECK(!memcmp(image.data(), data.data(), image.size_bytes()));
    }

    TEST_CASE("ManagedImage::clear() works correctly", "[ManagedImage]")
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

        Image::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image(imageInfo, data.data());
        REQUIRE(image.size_bytes() == data.size() * sizeof(data[0]));
        CHECK(!memcmp(image.data(), data.data(), image.size_bytes()));
        image.clear();
        CHECK(image.empty());
    }

    TEST_CASE("ManagedImage comparison operators work correctly", "[ManagedImage]")
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

        Image::Info imageInfo { };
        imageInfo.format = format;
        imageInfo.width = width;
        imageInfo.height = height;
        ManagedImage image0(imageInfo, data.data());
        ManagedImage image1(imageInfo, data.data());
        CHECK(image0 == image1);
        for (auto& pixel : image0.pixel_data<Pixel<format>::type>()) {
            pixel.r = rng.range<uint8_t>(0, 255);
            pixel.g = rng.range<uint8_t>(0, 255);
            pixel.b = rng.range<uint8_t>(0, 255);
        }
        CHECK(image0 != image1);
    }

} // namespace tests
} // namespace sys
} // namespace dst
