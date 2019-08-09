#pragma once

#include "Log.hpp"

#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>


#ifdef _WIN32
#define ASSERT(function, ...) { if (!(function)) __debugbreak(); { Log_Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#elif __APPLE__
#define ASSERT(x, ...) { if (!(x)) { Log_Error("Assertion Failed: {0}", __VA_ARGS__); std::cin.get(); } }
#elif __linux__
#define ASSERT(function, ...) { if (!(function)) std::cin.get(); { Log_Error("Assertion Failed: {0}", __VA_ARGS__); std::cin.get(); } }
#endif