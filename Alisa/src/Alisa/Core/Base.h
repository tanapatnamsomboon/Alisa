#pragma once

#include "Alisa/Core/PlatformDetection.h"	

#include <memory>

#ifdef ALISA_DEBUG
#	if defined(ALISA_PLATFORM_WINDOWS)
#		define ALISA_DEBUGBREAK() __debugbreak()
#	elif defined(ALISA_PLATFORM_LINUX)
#		include <signal.h>
#		define ALISA_DEBUGBREAK() raise(SIGTRAP)
#	else
#		error "Platform doesn't support debugbreak yet!"
#	endif
#	define ALISA_ENABLE_ASSERTS
#else
#	define ALISA_DEBUGBREAK()
#endif

namespace Alisa 
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}