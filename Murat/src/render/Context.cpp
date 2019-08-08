//
// Created by murat on 2019-08-08.
//

#include <Murat.hpp>
#include "Context.hpp"
#include "spdlog/spdlog.h"

Context::Context(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle) {
    if (windowHandle == nullptr)
        spdlog::error("Window handle is null!");
}

void Context::init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (status == 0)
        spdlog::info("Failed to initialize Glad!");

    spdlog::info("OpenGL Info:");
    spdlog::info("  Vendor: {0}", glGetString(GL_VENDOR));
    spdlog::info("  Renderer: {0}", glGetString(GL_RENDERER));
    spdlog::info("  Version: {0}", glGetString(GL_VERSION));

}

void Context::swapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
}