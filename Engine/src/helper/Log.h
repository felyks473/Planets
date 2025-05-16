#pragma once

#include <memory>

#include "spdlog/spdlog.h"

namespace Planets {

    class Log
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
    };
}

#define EH_CORE_TRACE(...) Planets::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define EH_CORE_INFO(...)  Planets::Log::GetCoreLogger()->info(__VA_ARGS__);
#define EH_CORE_WARN(...)  Planets::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define EH_CORE_ERROR(...) Planets::Log::GetCoreLogger()->error(__VA_ARGS__);
#define EH_CORE_FATAL(...) Planets::Log::GetCoreLogger()->fatal(__VA_ARGS__);
