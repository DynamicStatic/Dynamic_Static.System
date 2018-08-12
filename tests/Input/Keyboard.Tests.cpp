
/*
==========================================
  Copyright (c) 2017-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

namespace Dynamic_Static {
namespace Tests {



} // namespace Tests
} // namespace Dynamic_Static

#if 0
/*
==========================================
    Copyright (c) 2017 Dynamic_Static
    Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/System/Input.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include <catch.hpp>

namespace Dynamic_Static {
namespace System {
namespace Tests {

    static constexpr size_t TestCount { 7 };
    static constexpr size_t KeyCount { static_cast<size_t>(Keyboard::Key::Count) };

    TEST_CASE("ctor()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                 keyboard.up      (key) &&
                !keyboard.down    (key) &&
                !keyboard.held    (key) &&
                !keyboard.pressed (key) &&
                !keyboard.released(key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("Single update()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = dst::Random.probability(0.5f);
        }

        auto cachedState = keyboard.staged;
        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            if (cachedState[key_i] == DST_KEY_DOWN) {
                passed =
                    !keyboard.up      (key) &&
                     keyboard.down    (key) &&
                    !keyboard.held    (key) &&
                     keyboard.pressed (key) &&
                    !keyboard.released(key);
            } else
            if (cachedState[key_i] == DST_KEY_UP) {
                passed =
                     keyboard.up      (key) &&
                    !keyboard.down    (key) &&
                    !keyboard.held    (key) &&
                    !keyboard.pressed (key) &&
                    !keyboard.released(key);
            }

            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("update()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t frame_i = 0; frame_i < TestCount; ++frame_i) {
            for (size_t i = 0; i < KeyCount; ++i) {
                keyboard.staged[i] = dst::Random.probability(0.5f);
            }

            auto cachedPrevious = keyboard.current;
            auto cachedCurrent = keyboard.staged;
            keyboard.update();
            for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
                if (cachedPrevious[key_i] == DST_KEY_DOWN && cachedCurrent[key_i] == DST_KEY_DOWN) {
                    auto key = static_cast<Keyboard::Key>(key_i);
                    passed =
                        !keyboard.up      (key) &&
                         keyboard.down    (key) &&
                         keyboard.held    (key) &&
                        !keyboard.pressed (key) &&
                        !keyboard.released(key);
                } else
                if (cachedPrevious[key_i] == DST_KEY_DOWN && cachedCurrent[key_i] == DST_KEY_UP) {
                    auto key = static_cast<Keyboard::Key>(key_i);
                    passed =
                         keyboard.up      (key) &&
                        !keyboard.down    (key) &&
                        !keyboard.held    (key) &&
                        !keyboard.pressed (key) &&
                         keyboard.released(key);
                } else
                if (cachedPrevious[key_i] == DST_KEY_UP && cachedCurrent[key_i] == DST_KEY_DOWN) {
                    auto key = static_cast<Keyboard::Key>(key_i);
                    passed =
                        !keyboard.up      (key) &&
                         keyboard.down    (key) &&
                        !keyboard.held    (key) &&
                         keyboard.pressed (key) &&
                        !keyboard.released(key);
                } else
                if (cachedPrevious[key_i] == DST_KEY_UP && cachedCurrent[key_i] == DST_KEY_UP) {
                    auto key = static_cast<Keyboard::Key>(key_i);
                    passed =
                         keyboard.up      (key) &&
                        !keyboard.down    (key) &&
                        !keyboard.held    (key) &&
                        !keyboard.pressed (key) &&
                        !keyboard.released(key);
                }

                if (!passed) {
                    break;
                }
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("up()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = dst::Random.probability(0.5f);
        }

        keyboard.update();
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_UP;
        }

        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                 keyboard.up      (key) &&
                !keyboard.down    (key) &&
                !keyboard.held    (key) &&
                !keyboard.pressed (key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("down()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = dst::Random.probability(0.5f);
        }

        keyboard.update();
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_DOWN;
        }

        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                !keyboard.up      (key) &&
                 keyboard.down    (key) &&
                !keyboard.released(key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("held()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_DOWN;
        }

        keyboard.update();
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_DOWN;
        }

        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                !keyboard.up      (key) &&
                 keyboard.down    (key) &&
                 keyboard.held    (key) &&
                !keyboard.pressed (key) &&
                !keyboard.released(key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("pressed()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_UP;
        }

        keyboard.update();
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_DOWN;
        }

        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                !keyboard.up      (key) &&
                 keyboard.down    (key) &&
                !keyboard.held    (key) &&
                 keyboard.pressed (key) &&
                !keyboard.released(key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("released()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_DOWN;
        }

        keyboard.update();
        for (size_t i = 0; i < KeyCount; ++i) {
            keyboard.staged[i] = DST_KEY_UP;
        }

        keyboard.update();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                 keyboard.up      (key) &&
                !keyboard.down    (key) &&
                !keyboard.held    (key) &&
                !keyboard.pressed (key) &&
                 keyboard.released(key);

            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

    TEST_CASE("reset()", "[Keyboard]")
    {
        bool passed = true;
        Keyboard keyboard { };
        for (size_t frame_i = 0; frame_i < TestCount; ++frame_i) {
            for (size_t i = 0; i < KeyCount; ++i) {
                keyboard.staged[i] = dst::Random.probability(0.5f);
            }

            keyboard.update();
        }

        keyboard.reset();
        for (size_t key_i = 0; key_i < KeyCount; ++key_i) {
            auto key = static_cast<Keyboard::Key>(key_i);
            passed =
                 keyboard.up      (key) &&
                !keyboard.down    (key) &&
                !keyboard.held    (key) &&
                !keyboard.pressed (key) &&
                !keyboard.released(key);
            if (!passed) {
                break;
            }
        }

        REQUIRE(passed);
    }

} // namespace Tests
} // namespace System
} // namespace Dynamic_Static

#endif
