#pragma once

#ifdef _WIN32
#	ifdef _WIN64
#		define ALISA_PLATFORM_WINDOWS
#	else
#		error "x86 Builds are not supported!"
#	endif
#elif defined(__APPLE__) || defined(__MACH__)
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR == 1
#		error "IOS simulator is not supported!"
#	elif TARGET_OS_IPHONE == 1
#		define ALISA_PLATFORM_IOS
#		error "IOS is not supported!"
#	elif TARGET_OS_MAC == 1
#		define ALISA_PLATFORM_MACOS
#		error "MacOS is not currently supported!"
#	else
#		error "Unknown Apple platform!"
#	endif
#elif defined(__ANDROID__)
#	define ALISA_PLATFORM_ANDROID
#	error "Android is not currently supported!"
#elif defined(__linux__)
#	define ALISA_PLATFORM_LINUX
#	error "Linux is not currently supported!"
#else
#	error "Unknown platform!"
#endif
