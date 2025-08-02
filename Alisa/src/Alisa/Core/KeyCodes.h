#pragma once

#include "Alisa/Core/Base.h"
#include <magic_enum/magic_enum.hpp>

namespace Alisa
{
    // Use Win32 virtual-key codes as base
    enum class KeyCode : u8
    {
        A = 0x41,
        B, C, D, E, F,
        G, H, I, J, K,
        L, M, N, O, P,
        Q, R, S, T, U,
        V, W, X, Y, Z,

        Num0 = 0x30,
        Num1, Num2, Num3,
        Num4, Num5, Num6,
        Num7, Num8, Num9,

        Numpad0 = 0x60,
        Numpad1, Numpad2, Numpad3,
        Numpad4, Numpad5, Numpad6,
        Numpad7, Numpad8, Numpad9,

        F1 = 0x70,
        F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        Escape       = 0x1B,
        Tab          = 0x09,
        CapsLock     = 0x14,
        Shift        = 0x10,
        Control      = 0x11,
        Alt          = 0x12,
        Space        = 0x20,
        Enter        = 0x0D,
        Backspace    = 0x08,
        Delete       = 0x2E,

        LeftShift    = 0xA0,
        RightShift   = 0xA1,
        LeftControl  = 0xA2,
        RightControl = 0xA3,
        LeftAlt      = 0xA4,
        RightAlt     = 0xA5,

        LeftArrow    = 0x25,
        RightArrow   = 0x27,
        UpArrow      = 0x26,
        DownArrow    = 0x28,

        Unknown      = 0x00,
        MaxEnum      = 0xFF,
    };

    inline std::string KeyCodeToString(KeyCode keyCode)
    {
        return std::string(magic_enum::enum_name(keyCode));
    }
}
