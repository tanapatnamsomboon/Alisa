#pragma once

#include "Alisa/Core/Base.h"
#include <magic_enum/magic_enum.hpp>

namespace Alisa
{
    enum class MouseCode : u8
    {
        ButtonLeft   = 0x01,
        ButtonRight  = 0x02,
        ButtonMiddle = 0x04,
        Button4      = 0x05,
        Button5      = 0x06,

        Unknown      = 0xFF,
        MaxEnum      = 0xFF
    };

    inline std::string MouseCodeToString(MouseCode code)
    {
        return std::string(magic_enum::enum_name(code));
    }
}
