
/*
==========================================
  Copyright (c) 2019-2019 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Image.Ex.hpp"

#include "catch.hpp"

#include <vector>

namespace dst {
namespace sys {
namespace tests {

    static const std::vector<uint8_t> sTestImageSingleChannel16x16 {

    };

    TEST_CASE("TODO", "[Image]")
    {
        ImageEx image;
        CHECK(image.get_info().format == Format::Unknown);
        CHECK(image.get_info().width == 0);
        CHECK(image.get_info().height == 0);
    }

    TEST_CASE("TODO 0", "[Image]")
    {
        ImageEx::Info imageInfo { };
        imageInfo.format = Format::R8G8B8A8_Unorm;
        imageInfo.width = 16;
        imageInfo.height = 16;
        ImageEx image(imageInfo);
        CHECK(image.get_info().format == Format::R8G8B8A8_Unorm);
        CHECK(image.get_info().width == 16);
        CHECK(image.get_info().height == 16);
        auto sizeBytes = imageInfo.width * imageInfo.height * get_format_bytes_per_pixel(imageInfo.format);
        CHECK(image.size_bytes() == sizeBytes);
    }

    TEST_CASE("TODO 1", "[Image]")
    {
        RandomNumberGenerator rng;

        int width = 16;
        int height = 32;
        std::vector<uint8_t> data(width * height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                data[y * width + x] = rng.range(0, 256);
            }
        }

        ImageEx::Info imageInfo { };
        imageInfo.format = Format::R8_Unorm;
        imageInfo.width = width;
        imageInfo.height = height;
        ImageEx image(imageInfo);
        REQUIRE(image.size_bytes() == data.size());
        memcpy(image.data().data(), data.data(), image.size_bytes());
        CHECK(!memcmp(image.data().data(), data.data(), image.size_bytes()));
    }

#if 0
    TEST_CASE("TODO 0", "[Image]")
    {
        ImageEx image;
        CHECK_THROWS(image.write_png("c:/this/image/has/no/data.png"));
    }
#endif

} // namespace tests
} // namespace sys
} // namespace dst
