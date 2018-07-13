
/*
==========================================
  Copyright (c) 2011-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "Dynamic_Static/System/Defines.hpp"

#if defined(DYNAMIC_STATIC_GLFW_ENABLED)
#include "Dynamic_Static/System/GLFW.hpp"
#endif

#if defined(DYNAMIC_STATIC_SDL_ENABLED)
#include "Dynamic_Static/System/SDL.hpp"
#endif

#include <bitset>

#define DST_KEY_UP false
#define DST_KEY_DOWN true

namespace Dynamic_Static {
namespace System {

    /*
    * Provides high level control over Keyboard queries.
    */
    struct Keyboard final
    {
        /*
        * Specifies Keyboard keys.
        */
        enum class Key
        {
            // NOTE : The following table shows the symbolic constant names, hexadecimal values,
            //        and mouse or keyboard equivalents for the virtual-key codes used by Windows.
            //        The codes are listed in numeric order.
            //        http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx

            // Left                 = 0x01,
            // Right                = 0x02,

            ControlBreak         = 0x03,

            // Middle               = 0x04,
            // X1                   = 0x05,
            // X2                   = 0x06,

            Backspace            = 0x08,
            Tab                  = 0x09,
            Clear                = 0x0c,
            Enter                = 0x0d,
            Shift                = 0x10,
            Ctrl                 = 0x11,
            Alt                  = 0x12,
            Pause                = 0x13,
            CapsLock             = 0x14,

            IMEKanaMode          = 0x15,
            IMEHanguelMode       = 0x15,
            IMEHangulMode        = 0x15,
            IMEHanjaMode         = 0x19,
            IMEKanjiMode         = 0x19,

            Escape               = 0x1b,

            IMEConvert           = 0x1c,
            IMENonConvert        = 0x1d,
            IMEAccept            = 0x1e,
            IMEModeChangeRequest = 0x1f,

            SpaceBar             = 0x20,
            PageUp               = 0x21,
            PageDown             = 0x22,
            End                  = 0x23,
            Home                 = 0x24,

            LeftArrow            = 0x25,
            UpArrow              = 0x26,
            RightArrow           = 0x27,
            DownArrow            = 0x28,

            Select               = 0x29,
            Print                = 0x2a,
            Execute              = 0x2b,
            PrintScreen          = 0x2c,
            Insert               = 0x2d,
            Delete               = 0x2e,
            Help                 = 0x2f,

            Zero                 = 0x30,
            One                  = 0x31,
            Two                  = 0x32,
            Three                = 0x33,
            Four                 = 0x34,
            Five                 = 0x35,
            Six                  = 0x36,
            Seven                = 0x37,
            Eight                = 0x38,
            Nine                 = 0x39,

            A                    = 0x41,
            B                    = 0x42,
            C                    = 0x43,
            D                    = 0x44,
            E                    = 0x45,
            F                    = 0x46,
            G                    = 0x47,
            H                    = 0x48,
            I                    = 0x49,
            J                    = 0x4a,
            K                    = 0x4b,
            L                    = 0x4c,
            M                    = 0x4d,
            N                    = 0x4e,
            O                    = 0x4f,
            P                    = 0x50,
            Q                    = 0x51,
            R                    = 0x52,
            S                    = 0x53,
            T                    = 0x54,
            U                    = 0x55,
            V                    = 0x56,
            W                    = 0x57,
            X                    = 0x58,
            Y                    = 0x59,
            Z                    = 0x5a,

            LeftWindow           = 0x58,
            RightWindow          = 0x5c,
            Applications         = 0x5d,
            PowerSleep           = 0x5f,

            NumPad0              = 0x60,
            NumPad1              = 0x61,
            NumPad2              = 0x62,
            NumPad3              = 0x63,
            NumPad4              = 0x64,
            NumPad5              = 0x65,
            NumPad6              = 0x66,
            NumPad7              = 0x67,
            NumPad8              = 0x68,
            NumPad9              = 0x69,

            Multiply             = 0x6a,
            Add                  = 0x6b,
            Seperator            = 0x6c,
            Subtract             = 0x6d,
            Decimal              = 0x6e,
            Divide               = 0x6f,

            F1                   = 0x70,
            F2                   = 0x71,
            F3                   = 0x72,
            F4                   = 0x73,
            F5                   = 0x74,
            F6                   = 0x75,
            F7                   = 0x76,
            F8                   = 0x77,
            F9                   = 0x78,
            F10                  = 0x79,
            F11                  = 0x7a,
            F12                  = 0x7b,
            F13                  = 0x7c,
            F14                  = 0x7d,
            F15                  = 0x7e,
            F16                  = 0x7f,
            F17                  = 0x80,
            F18                  = 0x81,
            F19                  = 0x82,
            F20                  = 0x83,
            F21                  = 0x84,
            F22                  = 0x85,
            F23                  = 0x86,
            F24                  = 0x87,

            NumLock              = 0x90,
            ScrollLock           = 0x91,

            LeftShift            = 0xa0,
            RightShift           = 0xa1,
            LeftControl          = 0xa2,
            RightControl         = 0xa3,

            LeftMenu             = 0xa4,
            RightMenu            = 0xa5,
            BrowserBack          = 0xa6,
            BrowserForward       = 0xa7,
            BroserRefresh        = 0xa8,
            BrowserStop          = 0xa9,
            BrowserSearch        = 0xaa,
            BrowserFavorites     = 0xab,
            BrowserHome          = 0xac,

            VolumeMute           = 0xad,
            VolumeDown           = 0xae,
            VolumeUp             = 0xaf,

            MediaNextTrack       = 0xb0,
            MediaPreviousTrack   = 0xb1,
            MediaStop            = 0xb2,
            MediaPlayPause       = 0xb3,

            LaunchMail           = 0xb4,
            LaunchMediaSelect    = 0xb5,
            LaunchApp_1          = 0xb6,
            LaunchApp_2          = 0xb7,

            OEM_SemiColon        = 0xba, /* NOTE : Can vary by keyboard, ';:' is US standard */
            OEM_Plus             = 0xbb,
            OEM_Comma            = 0xbc,
            OEM_Minus            = 0xbd,
            OEM_Period           = 0xbe,
            OEM_ForwardSlash     = 0xbf, /*!< NOTE : Can vary by keyboard, '/?' is US standard */
            OEM_Tilde            = 0xc0, /*!< NOTE : Can vary by keyboard, '`~' is US standard */
            OEM_OpenBracket      = 0xdb, /*!< NOTE : Can vary by keyboard, '[{' is US standard */
            OEM_BackSlash        = 0xdc, /*!< NOTE : Can vary by keyboard, '\|' is US standard */
            OEM_CloseBracket     = 0xdd, /*!< NOTE : Can vary by keyboard, ']}' is US standard */
            OEM_Quote            = 0xde, /*!< NOTE : Can vary by keyboard, ''"' is US standard */
            OEM_Misc             = 0xdf, /*!< NOTE : Varies by keyboard */
            OEM_102              = 0xe2,

            Process              = 0xe5,

            Packet               = 0xe7, /*!< NOTE : Used to pass Unicode characters as keystrokes */

            Attn                 = 0xf6,
            CrSel                = 0xf7,
            ExSel                = 0xf8,
            EraseEOF             = 0xf9,
            Play                 = 0xfa,
            Zoom                 = 0xfb,
            PA1                  = 0xfd,

            OEM_Clear            = 0xfe,

            Unknown,
            Count,
            Any,
        };

        /*
        * Represents a Keyboard's state at a single moment.
        */
        using State = std::bitset<static_cast<size_t>(Key::Count)>;

        /*
        * This Keyboard's previous state
        */
        State previous { };

        /*
        * This Keyboard's current state
        */
        State current { };

        /*
        * This Keyboard's staging state, this state will be applied when update() is called
        */
        State staged { };

        /*
        * Gets a value indicating whether or not a given Key is up.
        * @param [in] key The Key to check
        * @return Whether or not the given Key is up
        */
        inline bool up(Key key) const
        {
            return current[static_cast<size_t>(key)] == DST_KEY_UP;
        }

        /*
        * Gets a value indicating whether or not a given Key is down.
        * @param [in] key The Key to check
        * @return Whether or not the given Key is down
        */
        inline bool down(Key key) const
        {
            return current[static_cast<size_t>(key)] == DST_KEY_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Key has been held.
        * @param [in] key The Key to check
        * @return Whether or not the given Key has been held
        */
        inline bool held(Key key) const
        {
            return
                previous[static_cast<size_t>(key)] == DST_KEY_DOWN &&
                current [static_cast<size_t>(key)] == DST_KEY_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Key has been pressed.
        * @param [in] key The Key to check
        * @return Whether or not the given Key has been pressed
        */
        inline bool pressed(Key key) const
        {
            return
                previous[static_cast<size_t>(key)] == DST_KEY_UP &&
                current [static_cast<size_t>(key)] == DST_KEY_DOWN;
        }

        /*
        * Gets a value indicating whether or not a given Key has been released.
        * @param [in] key The Key to check
        * @return Whether or not the given Key has been released
        */
        inline bool released(Key key) const
        {
            return
                previous[static_cast<size_t>(key)] == DST_KEY_DOWN &&
                current [static_cast<size_t>(key)] == DST_KEY_UP;
        }

        /*
        * Updates this Keyboard with its staged state.
        * \n NOTE : This method must be called periodically to keep this Keyboard up to date.
        */
        inline void update()
        {
            previous = current;
            current = staged;
        }

        /*
        * Resets this Keyboard.
        */
        inline void reset()
        {
            previous.reset();
            current.reset();
            staged.reset();
        }
    };

#if defined(DYNAMIC_STATIC_GLFW_ENABLED)

    /*
    * Converts a GLFW key to a Keyboard::Key.
    * @param [in] glfwKey The GLFW key to convert to a Keyboard::Key
    * @return The converted Keyboard::Key
    */
    inline Keyboard::Key glfw_to_dst_key(int glfwKey)
    {
        auto key = Keyboard::Key::Unknown;
        switch (glfwKey) {
            case GLFW_KEY_SPACE        : key = Keyboard::Key::SpaceBar;         break;
            case GLFW_KEY_APOSTROPHE   : key = Keyboard::Key::OEM_Quote;        break;
            case GLFW_KEY_COMMA        : key = Keyboard::Key::OEM_Comma;        break;
            case GLFW_KEY_MINUS        : key = Keyboard::Key::OEM_Minus;        break;
            case GLFW_KEY_PERIOD       : key = Keyboard::Key::OEM_Period;       break;
            case GLFW_KEY_SLASH        : key = Keyboard::Key::OEM_ForwardSlash; break;
            case GLFW_KEY_0            : key = Keyboard::Key::Zero;             break;
            case GLFW_KEY_1            : key = Keyboard::Key::One;              break;
            case GLFW_KEY_2            : key = Keyboard::Key::Two;              break;
            case GLFW_KEY_3            : key = Keyboard::Key::Three;            break;
            case GLFW_KEY_4            : key = Keyboard::Key::Four;             break;
            case GLFW_KEY_5            : key = Keyboard::Key::Five;             break;
            case GLFW_KEY_6            : key = Keyboard::Key::Six;              break;
            case GLFW_KEY_7            : key = Keyboard::Key::Seven;            break;
            case GLFW_KEY_8            : key = Keyboard::Key::Eight;            break;
            case GLFW_KEY_9            : key = Keyboard::Key::Nine;             break;
            case GLFW_KEY_SEMICOLON    : key = Keyboard::Key::OEM_SemiColon;    break;
            case GLFW_KEY_EQUAL        : key = Keyboard::Key::OEM_Plus;         break;
            case GLFW_KEY_A            : key = Keyboard::Key::A;                break;
            case GLFW_KEY_B            : key = Keyboard::Key::B;                break;
            case GLFW_KEY_C            : key = Keyboard::Key::C;                break;
            case GLFW_KEY_D            : key = Keyboard::Key::D;                break;
            case GLFW_KEY_E            : key = Keyboard::Key::E;                break;
            case GLFW_KEY_F            : key = Keyboard::Key::F;                break;
            case GLFW_KEY_G            : key = Keyboard::Key::G;                break;
            case GLFW_KEY_H            : key = Keyboard::Key::H;                break;
            case GLFW_KEY_I            : key = Keyboard::Key::I;                break;
            case GLFW_KEY_J            : key = Keyboard::Key::J;                break;
            case GLFW_KEY_K            : key = Keyboard::Key::K;                break;
            case GLFW_KEY_L            : key = Keyboard::Key::L;                break;
            case GLFW_KEY_M            : key = Keyboard::Key::M;                break;
            case GLFW_KEY_N            : key = Keyboard::Key::N;                break;
            case GLFW_KEY_O            : key = Keyboard::Key::O;                break;
            case GLFW_KEY_P            : key = Keyboard::Key::P;                break;
            case GLFW_KEY_Q            : key = Keyboard::Key::Q;                break;
            case GLFW_KEY_R            : key = Keyboard::Key::R;                break;
            case GLFW_KEY_S            : key = Keyboard::Key::S;                break;
            case GLFW_KEY_T            : key = Keyboard::Key::T;                break;
            case GLFW_KEY_U            : key = Keyboard::Key::U;                break;
            case GLFW_KEY_V            : key = Keyboard::Key::V;                break;
            case GLFW_KEY_W            : key = Keyboard::Key::W;                break;
            case GLFW_KEY_X            : key = Keyboard::Key::X;                break;
            case GLFW_KEY_Y            : key = Keyboard::Key::Y;                break;
            case GLFW_KEY_Z            : key = Keyboard::Key::Z;                break;
            case GLFW_KEY_LEFT_BRACKET : key = Keyboard::Key::OEM_OpenBracket;  break;
            case GLFW_KEY_BACKSLASH    : key = Keyboard::Key::OEM_BackSlash;    break;
            case GLFW_KEY_RIGHT_BRACKET: key = Keyboard::Key::OEM_CloseBracket; break;
            case GLFW_KEY_GRAVE_ACCENT : key = Keyboard::Key::OEM_Tilde;        break;
            case GLFW_KEY_WORLD_1      : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_WORLD_2      : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_ESCAPE       : key = Keyboard::Key::Escape;           break;
            case GLFW_KEY_ENTER        : key = Keyboard::Key::Enter;            break;
            case GLFW_KEY_TAB          : key = Keyboard::Key::Tab;              break;
            case GLFW_KEY_BACKSPACE    : key = Keyboard::Key::Backspace;        break;
            case GLFW_KEY_INSERT       : key = Keyboard::Key::Insert;           break;
            case GLFW_KEY_DELETE       : key = Keyboard::Key::Delete;           break;
            case GLFW_KEY_RIGHT        : key = Keyboard::Key::RightArrow;       break;
            case GLFW_KEY_LEFT         : key = Keyboard::Key::LeftArrow;        break;
            case GLFW_KEY_DOWN         : key = Keyboard::Key::DownArrow;        break;
            case GLFW_KEY_UP           : key = Keyboard::Key::UpArrow;          break;
            case GLFW_KEY_PAGE_UP      : key = Keyboard::Key::PageUp;           break;
            case GLFW_KEY_PAGE_DOWN    : key = Keyboard::Key::PageDown;         break;
            case GLFW_KEY_HOME         : key = Keyboard::Key::Home;             break;
            case GLFW_KEY_END          : key = Keyboard::Key::End;              break;
            case GLFW_KEY_CAPS_LOCK    : key = Keyboard::Key::CapsLock;         break;
            case GLFW_KEY_SCROLL_LOCK  : key = Keyboard::Key::ScrollLock;       break;
            case GLFW_KEY_NUM_LOCK     : key = Keyboard::Key::NumLock;          break;
            case GLFW_KEY_PRINT_SCREEN : key = Keyboard::Key::PrintScreen;      break;
            case GLFW_KEY_PAUSE        : key = Keyboard::Key::Pause;            break;
            case GLFW_KEY_F1           : key = Keyboard::Key::F1;               break;
            case GLFW_KEY_F2           : key = Keyboard::Key::F2;               break;
            case GLFW_KEY_F3           : key = Keyboard::Key::F3;               break;
            case GLFW_KEY_F4           : key = Keyboard::Key::F4;               break;
            case GLFW_KEY_F5           : key = Keyboard::Key::F5;               break;
            case GLFW_KEY_F6           : key = Keyboard::Key::F6;               break;
            case GLFW_KEY_F7           : key = Keyboard::Key::F7;               break;
            case GLFW_KEY_F8           : key = Keyboard::Key::F8;               break;
            case GLFW_KEY_F9           : key = Keyboard::Key::F9;               break;
            case GLFW_KEY_F10          : key = Keyboard::Key::F10;              break;
            case GLFW_KEY_F11          : key = Keyboard::Key::F11;              break;
            case GLFW_KEY_F12          : key = Keyboard::Key::F12;              break;
            case GLFW_KEY_F13          : key = Keyboard::Key::F13;              break;
            case GLFW_KEY_F14          : key = Keyboard::Key::F14;              break;
            case GLFW_KEY_F15          : key = Keyboard::Key::F15;              break;
            case GLFW_KEY_F16          : key = Keyboard::Key::F16;              break;
            case GLFW_KEY_F17          : key = Keyboard::Key::F17;              break;
            case GLFW_KEY_F18          : key = Keyboard::Key::F18;              break;
            case GLFW_KEY_F19          : key = Keyboard::Key::F19;              break;
            case GLFW_KEY_F20          : key = Keyboard::Key::F20;              break;
            case GLFW_KEY_F21          : key = Keyboard::Key::F21;              break;
            case GLFW_KEY_F22          : key = Keyboard::Key::F22;              break;
            case GLFW_KEY_F23          : key = Keyboard::Key::F23;              break;
            case GLFW_KEY_F24          : key = Keyboard::Key::F24;              break;
            case GLFW_KEY_F25          : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_KP_0         : key = Keyboard::Key::NumPad0;          break;
            case GLFW_KEY_KP_1         : key = Keyboard::Key::NumPad1;          break;
            case GLFW_KEY_KP_2         : key = Keyboard::Key::NumPad2;          break;
            case GLFW_KEY_KP_3         : key = Keyboard::Key::NumPad3;          break;
            case GLFW_KEY_KP_4         : key = Keyboard::Key::NumPad4;          break;
            case GLFW_KEY_KP_5         : key = Keyboard::Key::NumPad5;          break;
            case GLFW_KEY_KP_6         : key = Keyboard::Key::NumPad6;          break;
            case GLFW_KEY_KP_7         : key = Keyboard::Key::NumPad7;          break;
            case GLFW_KEY_KP_8         : key = Keyboard::Key::NumPad8;          break;
            case GLFW_KEY_KP_9         : key = Keyboard::Key::NumPad9;          break;
            case GLFW_KEY_KP_DECIMAL   : key = Keyboard::Key::Decimal;          break;
            case GLFW_KEY_KP_DIVIDE    : key = Keyboard::Key::Divide;           break;
            case GLFW_KEY_KP_MULTIPLY  : key = Keyboard::Key::Multiply;         break;
            case GLFW_KEY_KP_SUBTRACT  : key = Keyboard::Key::Subtract;         break;
            case GLFW_KEY_KP_ADD       : key = Keyboard::Key::Add;              break;
            case GLFW_KEY_KP_ENTER     : key = Keyboard::Key::Enter;            break;
            case GLFW_KEY_KP_EQUAL     : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_LEFT_SHIFT   : key = Keyboard::Key::LeftShift;        break;
            case GLFW_KEY_LEFT_CONTROL : key = Keyboard::Key::LeftControl;      break;
            case GLFW_KEY_LEFT_ALT     : key = Keyboard::Key::Alt;              break;
            case GLFW_KEY_LEFT_SUPER   : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_RIGHT_SHIFT  : key = Keyboard::Key::RightShift;       break;
            case GLFW_KEY_RIGHT_CONTROL: key = Keyboard::Key::RightControl;     break;
            case GLFW_KEY_RIGHT_ALT    : key = Keyboard::Key::Alt;              break;
            case GLFW_KEY_RIGHT_SUPER  : key = Keyboard::Key::Unknown;          break;
            case GLFW_KEY_MENU         : key = Keyboard::Key::Unknown;          break;
            default:                     key = Keyboard::Key::Unknown;          break;
        }
        return key;
    }

#endif // #if defined(DYNAMIC_STATIC_GLFW_ENABLED)

#if defined(DYNAMIC_STATIC_SDL_ENABLED)

    /*
    * Converts an SDL key to a Keyboard::Key.
    * @param [in] sdlScancode The SDL_Scancode to convert to a Keyboard::Key
    * @return The converted Keyboard::Key
    */
    inline Keyboard::Key sdl_to_dst_key(SDL_Scancode sdlScancode)
    {
        auto key = Keyboard::Key::Unknown;
        switch (sdlScancode) {
            case SDL_SCANCODE_UNKNOWN            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_A                  : key = Keyboard::Key::A;                break;
            case SDL_SCANCODE_B                  : key = Keyboard::Key::B;                break;
            case SDL_SCANCODE_C                  : key = Keyboard::Key::C;                break;
            case SDL_SCANCODE_D                  : key = Keyboard::Key::D;                break;
            case SDL_SCANCODE_E                  : key = Keyboard::Key::E;                break;
            case SDL_SCANCODE_F                  : key = Keyboard::Key::F;                break;
            case SDL_SCANCODE_G                  : key = Keyboard::Key::G;                break;
            case SDL_SCANCODE_H                  : key = Keyboard::Key::H;                break;
            case SDL_SCANCODE_I                  : key = Keyboard::Key::I;                break;
            case SDL_SCANCODE_J                  : key = Keyboard::Key::J;                break;
            case SDL_SCANCODE_K                  : key = Keyboard::Key::K;                break;
            case SDL_SCANCODE_L                  : key = Keyboard::Key::L;                break;
            case SDL_SCANCODE_M                  : key = Keyboard::Key::M;                break;
            case SDL_SCANCODE_N                  : key = Keyboard::Key::N;                break;
            case SDL_SCANCODE_O                  : key = Keyboard::Key::O;                break;
            case SDL_SCANCODE_P                  : key = Keyboard::Key::P;                break;
            case SDL_SCANCODE_Q                  : key = Keyboard::Key::Q;                break;
            case SDL_SCANCODE_R                  : key = Keyboard::Key::R;                break;
            case SDL_SCANCODE_S                  : key = Keyboard::Key::S;                break;
            case SDL_SCANCODE_T                  : key = Keyboard::Key::T;                break;
            case SDL_SCANCODE_U                  : key = Keyboard::Key::U;                break;
            case SDL_SCANCODE_V                  : key = Keyboard::Key::V;                break;
            case SDL_SCANCODE_W                  : key = Keyboard::Key::W;                break;
            case SDL_SCANCODE_X                  : key = Keyboard::Key::X;                break;
            case SDL_SCANCODE_Y                  : key = Keyboard::Key::Y;                break;
            case SDL_SCANCODE_Z                  : key = Keyboard::Key::Z;                break;
            case SDL_SCANCODE_1                  : key = Keyboard::Key::One;              break;
            case SDL_SCANCODE_2                  : key = Keyboard::Key::Two;              break;
            case SDL_SCANCODE_3                  : key = Keyboard::Key::Three;            break;
            case SDL_SCANCODE_4                  : key = Keyboard::Key::Four;             break;
            case SDL_SCANCODE_5                  : key = Keyboard::Key::Five;             break;
            case SDL_SCANCODE_6                  : key = Keyboard::Key::Six;              break;
            case SDL_SCANCODE_7                  : key = Keyboard::Key::Seven;            break;
            case SDL_SCANCODE_8                  : key = Keyboard::Key::Eight;            break;
            case SDL_SCANCODE_9                  : key = Keyboard::Key::Nine;             break;
            case SDL_SCANCODE_0                  : key = Keyboard::Key::Zero;             break;
            case SDL_SCANCODE_RETURN             : key = Keyboard::Key::Enter;            break;
            case SDL_SCANCODE_ESCAPE             : key = Keyboard::Key::Escape;           break;
            case SDL_SCANCODE_BACKSPACE          : key = Keyboard::Key::Backspace;        break;
            case SDL_SCANCODE_TAB                : key = Keyboard::Key::Tab;              break;
            case SDL_SCANCODE_SPACE              : key = Keyboard::Key::SpaceBar;         break;
            case SDL_SCANCODE_MINUS              : key = Keyboard::Key::OEM_Minus;        break;
            case SDL_SCANCODE_EQUALS             : key = Keyboard::Key::OEM_Plus;         break;
            case SDL_SCANCODE_LEFTBRACKET        : key = Keyboard::Key::OEM_OpenBracket;  break;
            case SDL_SCANCODE_RIGHTBRACKET       : key = Keyboard::Key::OEM_CloseBracket; break;
            case SDL_SCANCODE_BACKSLASH          : key = Keyboard::Key::OEM_BackSlash;    break;
            case SDL_SCANCODE_NONUSHASH          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_SEMICOLON          : key = Keyboard::Key::OEM_SemiColon;    break;
            case SDL_SCANCODE_APOSTROPHE         : key = Keyboard::Key::OEM_Quote;        break;
            case SDL_SCANCODE_GRAVE              : key = Keyboard::Key::OEM_Tilde;        break;
            case SDL_SCANCODE_COMMA              : key = Keyboard::Key::OEM_Comma;        break;
            case SDL_SCANCODE_PERIOD             : key = Keyboard::Key::OEM_Period;       break;
            case SDL_SCANCODE_SLASH              : key = Keyboard::Key::OEM_ForwardSlash; break;
            case SDL_SCANCODE_CAPSLOCK           : key = Keyboard::Key::CapsLock;         break;
            case SDL_SCANCODE_F1                 : key = Keyboard::Key::F1;               break;
            case SDL_SCANCODE_F2                 : key = Keyboard::Key::F2;               break;
            case SDL_SCANCODE_F3                 : key = Keyboard::Key::F3;               break;
            case SDL_SCANCODE_F4                 : key = Keyboard::Key::F4;               break;
            case SDL_SCANCODE_F5                 : key = Keyboard::Key::F5;               break;
            case SDL_SCANCODE_F6                 : key = Keyboard::Key::F6;               break;
            case SDL_SCANCODE_F7                 : key = Keyboard::Key::F7;               break;
            case SDL_SCANCODE_F8                 : key = Keyboard::Key::F8;               break;
            case SDL_SCANCODE_F9                 : key = Keyboard::Key::F9;               break;
            case SDL_SCANCODE_F10                : key = Keyboard::Key::F10;              break;
            case SDL_SCANCODE_F11                : key = Keyboard::Key::F11;              break;
            case SDL_SCANCODE_F12                : key = Keyboard::Key::F12;              break;
            case SDL_SCANCODE_PRINTSCREEN        : key = Keyboard::Key::PrintScreen;      break;
            case SDL_SCANCODE_SCROLLLOCK         : key = Keyboard::Key::ScrollLock;       break;
            case SDL_SCANCODE_PAUSE              : key = Keyboard::Key::Pause;            break;
            case SDL_SCANCODE_INSERT             : key = Keyboard::Key::Insert;           break;
            case SDL_SCANCODE_HOME               : key = Keyboard::Key::Home;             break;
            case SDL_SCANCODE_PAGEUP             : key = Keyboard::Key::PageUp;           break;
            case SDL_SCANCODE_DELETE             : key = Keyboard::Key::Delete;           break;
            case SDL_SCANCODE_END                : key = Keyboard::Key::End;              break;
            case SDL_SCANCODE_PAGEDOWN           : key = Keyboard::Key::PageDown;         break;
            case SDL_SCANCODE_RIGHT              : key = Keyboard::Key::RightArrow;       break;
            case SDL_SCANCODE_LEFT               : key = Keyboard::Key::LeftArrow;        break;
            case SDL_SCANCODE_DOWN               : key = Keyboard::Key::DownArrow;        break;
            case SDL_SCANCODE_UP                 : key = Keyboard::Key::UpArrow;          break;
            case SDL_SCANCODE_NUMLOCKCLEAR       : key = Keyboard::Key::NumLock;          break;
            case SDL_SCANCODE_KP_DIVIDE          : key = Keyboard::Key::Divide;           break;
            case SDL_SCANCODE_KP_MULTIPLY        : key = Keyboard::Key::Multiply;         break;
            case SDL_SCANCODE_KP_MINUS           : key = Keyboard::Key::OEM_Minus;        break;
            case SDL_SCANCODE_KP_PLUS            : key = Keyboard::Key::OEM_Plus;         break;
            case SDL_SCANCODE_KP_ENTER           : key = Keyboard::Key::Enter;            break;
            case SDL_SCANCODE_KP_1               : key = Keyboard::Key::NumPad1;          break;
            case SDL_SCANCODE_KP_2               : key = Keyboard::Key::NumPad2;          break;
            case SDL_SCANCODE_KP_3               : key = Keyboard::Key::NumPad3;          break;
            case SDL_SCANCODE_KP_4               : key = Keyboard::Key::NumPad4;          break;
            case SDL_SCANCODE_KP_5               : key = Keyboard::Key::NumPad5;          break;
            case SDL_SCANCODE_KP_6               : key = Keyboard::Key::NumPad6;          break;
            case SDL_SCANCODE_KP_7               : key = Keyboard::Key::NumPad7;          break;
            case SDL_SCANCODE_KP_8               : key = Keyboard::Key::NumPad8;          break;
            case SDL_SCANCODE_KP_9               : key = Keyboard::Key::NumPad9;          break;
            case SDL_SCANCODE_KP_0               : key = Keyboard::Key::NumPad0;          break;
            case SDL_SCANCODE_KP_PERIOD          : key = Keyboard::Key::OEM_Period;       break;
            case SDL_SCANCODE_NONUSBACKSLASH     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_APPLICATION        : key = Keyboard::Key::Applications;     break;
            case SDL_SCANCODE_POWER              : key = Keyboard::Key::PowerSleep;       break;
            case SDL_SCANCODE_KP_EQUALS          : key = Keyboard::Key::OEM_Plus;         break;
            case SDL_SCANCODE_F13                : key = Keyboard::Key::F13;              break;
            case SDL_SCANCODE_F14                : key = Keyboard::Key::F14;              break;
            case SDL_SCANCODE_F15                : key = Keyboard::Key::F15;              break;
            case SDL_SCANCODE_F16                : key = Keyboard::Key::F16;              break;
            case SDL_SCANCODE_F17                : key = Keyboard::Key::F17;              break;
            case SDL_SCANCODE_F18                : key = Keyboard::Key::F18;              break;
            case SDL_SCANCODE_F19                : key = Keyboard::Key::F19;              break;
            case SDL_SCANCODE_F20                : key = Keyboard::Key::F20;              break;
            case SDL_SCANCODE_F21                : key = Keyboard::Key::F21;              break;
            case SDL_SCANCODE_F22                : key = Keyboard::Key::F22;              break;
            case SDL_SCANCODE_F23                : key = Keyboard::Key::F23;              break;
            case SDL_SCANCODE_F24                : key = Keyboard::Key::F24;              break;
            case SDL_SCANCODE_EXECUTE            : key = Keyboard::Key::Execute;          break;
            case SDL_SCANCODE_HELP               : key = Keyboard::Key::Help;             break;
            case SDL_SCANCODE_MENU               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_SELECT             : key = Keyboard::Key::Select;           break;
            case SDL_SCANCODE_STOP               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AGAIN              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_UNDO               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CUT                : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_COPY               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_PASTE              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_FIND               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_MUTE               : key = Keyboard::Key::VolumeMute;       break;
            case SDL_SCANCODE_VOLUMEUP           : key = Keyboard::Key::VolumeUp;         break;
            case SDL_SCANCODE_VOLUMEDOWN         : key = Keyboard::Key::VolumeDown;       break;
            case SDL_SCANCODE_KP_COMMA           : key = Keyboard::Key::OEM_Comma;        break;
            case SDL_SCANCODE_KP_EQUALSAS400     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL1     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL2     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL3     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL4     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL5     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL6     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL7     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL8     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_INTERNATIONAL9     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG1              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG2              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG3              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG4              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG5              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG6              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG7              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG8              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LANG9              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_ALTERASE           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_SYSREQ             : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CANCEL             : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CLEAR              : key = Keyboard::Key::Clear;            break;
            case SDL_SCANCODE_PRIOR              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_RETURN2            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_SEPARATOR          : key = Keyboard::Key::Seperator;        break;
            case SDL_SCANCODE_OUT                : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_OPER               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CLEARAGAIN         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CRSEL              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_EXSEL              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_00              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_000             : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_THOUSANDSSEPARATOR : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_DECIMALSEPARATOR   : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CURRENCYUNIT       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CURRENCYSUBUNIT    : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_LEFTPAREN       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_RIGHTPAREN      : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_LEFTBRACE       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_RIGHTBRACE      : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_TAB             : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_BACKSPACE       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_A               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_B               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_C               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_D               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_E               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_F               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_XOR             : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_POWER           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_PERCENT         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_LESS            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_GREATER         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_AMPERSAND       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_DBLAMPERSAND    : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_VERTICALBAR     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_DBLVERTICALBAR  : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_COLON           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_HASH            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_SPACE           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_AT              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_EXCLAM          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMSTORE        : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMRECALL       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMCLEAR        : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMADD          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMSUBTRACT     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMMULTIPLY     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_MEMDIVIDE       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_PLUSMINUS       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_CLEAR           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_CLEARENTRY      : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_BINARY          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_OCTAL           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_DECIMAL         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KP_HEXADECIMAL     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_LCTRL              : key = Keyboard::Key::LeftControl;      break;
            case SDL_SCANCODE_LSHIFT             : key = Keyboard::Key::LeftShift;        break;
            case SDL_SCANCODE_LALT               : key = Keyboard::Key::Alt;              break;
            case SDL_SCANCODE_LGUI               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_RCTRL              : key = Keyboard::Key::RightControl;     break;
            case SDL_SCANCODE_RSHIFT             : key = Keyboard::Key::RightShift;       break;
            case SDL_SCANCODE_RALT               : key = Keyboard::Key::Alt;              break;
            case SDL_SCANCODE_RGUI               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_MODE               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIONEXT          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOPREV          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOSTOP          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOPLAY          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOMUTE          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_MEDIASELECT        : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_WWW                : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_MAIL               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_CALCULATOR         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_COMPUTER           : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_SEARCH          : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_HOME            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_BACK            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_FORWARD         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_STOP            : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_REFRESH         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AC_BOOKMARKS       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_BRIGHTNESSDOWN     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_BRIGHTNESSUP       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_DISPLAYSWITCH      : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KBDILLUMTOGGLE     : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KBDILLUMDOWN       : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_KBDILLUMUP         : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_EJECT              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_SLEEP              : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_APP1               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_APP2               : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOREWIND        : key = Keyboard::Key::Unknown;          break;
            case SDL_SCANCODE_AUDIOFASTFORWARD   : key = Keyboard::Key::Unknown;          break;
            case SDL_NUM_SCANCODES               : key = Keyboard::Key::Unknown;          break;
            default:                               key = Keyboard::Key::Unknown;          break;
        }
        return key;
    }

#endif // #if defined(DYNAMIC_STATIC_SDL_ENABLED)

} // namespace System
} // namespace Dynamic_Static
