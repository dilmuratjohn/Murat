//
// Created by murat on 2019-08-09.
//

#include "Log.hpp"

namespace Murat {
    std::shared_ptr<spdlog::logger> Log::s_Logger;

    void Log::init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_Logger = spdlog::stdout_color_mt("Murat");
        s_Logger->set_level(spdlog::level::trace);
    }
}