#pragma once

#include <cstdint>

namespace Alisa
{
    // Interger types
    using i8  = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    // Floating-point types
    using f32 = float;
    using f64 = double;

    // Character types for Unicode support
    using utf8  = char8_t;  // UTF-8 code unit
    using utf16 = char16_t; // UTF-16 code unit
    using utf32 = char32_t; // UTF-32 code unit (Unicode code point)

    using wchar = wchar_t;  // Wide character (platform-dependent)
}
