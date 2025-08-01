#pragma once

#include "Alisa/Core/Base.h"
#include <source_location>

#ifdef ALISA_ENABLE_ASSERTS

#   define ALISA_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ALISA##type##ERROR(msg, __VA_ARGS__); ALISA_DEBUGBREAK(); std::unreachable(); } }
#   define ALISA_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ALISA_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#   define ALISA_INTERNAL_ASSERT_NO_MSG(type, check) ALISA_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ALISA_STRINGIFY_MACRO(check), std::source_location::current().file_name(), std::source_location::current().line())

#   define ALISA_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#   define ALISA_INTERNAL_ASSERT_GET_MACRO(...) ALISA_EXPAND_MACRO(ALISA_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ALISA_INTERNAL_ASSERT_WITH_MSG, ALISA_INTERNAL_ASSERT_NO_MSG))

#   define ALISA_ASSERT(...)      ALISA_EXPAND_MACRO(ALISA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#   define ALISA_CORE_ASSERT(...) ALISA_EXPAND_MACRO(ALISA_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#   define ALISA_ASSERT(...)      (void)0
#   define ALISA_CORE_ASSERT(...) (void)0
#endif // ALISA_ENABLE_ASSERTS
