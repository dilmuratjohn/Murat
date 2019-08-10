# Copyright (C) 2019 Murat

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(Application)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        Sandbox.cpp
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        )

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        )

include_directories(
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/src/core"
        "${CMAKE_SOURCE_DIR}/src/imgui"
        "${CMAKE_SOURCE_DIR}/src/model"
        "${CMAKE_SOURCE_DIR}/vendor"
        "${CMAKE_SOURCE_DIR}/vendor/imgui"
        "${CMAKE_SOURCE_DIR}/vendor/glfw/include"
        "${CMAKE_SOURCE_DIR}/vendor/glad/include"
        "${CMAKE_SOURCE_DIR}/vendor/spdlog/include"
        "${CMAKE_SOURCE_DIR}/vendor/assimp/include"
)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# OpenGL
find_package(OpenGL REQUIRED)

# ASSIMP
add_subdirectory("vendor/assimp")

# Glad
add_library(Glad "vendor/glad/src/glad.c")

# GLFW
add_subdirectory("vendor/glfw")

# GLM
add_subdirectory("vendor/glm")

# ImGui
add_library(imgui
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imconfig.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_internal.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imstb_rectpack.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imstb_textedit.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imstb_truetype.h"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui.cpp"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_draw.cpp"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_widgets.cpp"
        "${CMAKE_SOURCE_DIR}/vendor/imgui/imgui_demo.cpp"
        )

# stb_image
add_library(stb_image "vendor/stb_image/stb_image.cpp")

# spd_log
add_subdirectory("vendor/spdlog")

set(Libs glfw assimp stb_image Glad imgui)
target_link_libraries(${PROJECT_NAME} ${Libs})


