//
// Created by murat on 2019-08-09.
//

#pragma once


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/include/spdlog/sinks/stdout_color_sinks.h>

namespace Murat {

    class Log {
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger> &getLogger() { return s_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };

}

// Core log macros
#define Log_Trace(...)    ::Murat::Log::getLogger()->trace(__VA_ARGS__)
#define Log_Info(...)     ::Murat::Log::getLogger()->info(__VA_ARGS__)
#define Log_Warn(...)     ::Murat::Log::getLogger()->warn(__VA_ARGS__)
#define Log_Error(...)    ::Murat::Log::getLogger()->error(__VA_ARGS__)
#define Log_Critical(...) ::Murat::Log::getLogger()->critical(__VA_ARGS__)

