#pragma once

#include "Alisa/Core/Base.h"
#include <spdlog/spdlog.h>

namespace Alisa
{
	class Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define ALISA_CORE_TRACE(...) ::Alisa::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALISA_CORE_INFO(...)  ::Alisa::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALISA_CORE_WARN(...)  ::Alisa::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALISA_CORE_ERROR(...) ::Alisa::Log::GetCoreLogger()->error(__VA_ARGS__)

#define ALISA_TRACE(...)	  ::Alisa::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ALISA_INFO(...)		  ::Alisa::Log::GetClientLogger()->info(__VA_ARGS__)
#define ALISA_WARN(...)		  ::Alisa::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ALISA_ERROR(...)	  ::Alisa::Log::GetClientLogger()->error(__VA_ARGS__)

#define ALISA_LOG(...)	      ALISA_INFO(__VA_ARGS__)