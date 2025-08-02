#include "pch.h"
#include "Alisa/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Alisa
{
    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        spdlog::set_pattern("[%T] [%^%-5l%$] %n | %v");
        s_CoreLogger = spdlog::stdout_color_mt("ALISA");
        s_ClientLogger = spdlog::stdout_color_mt("APP");

        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);
    }
} // namespace Alisa
