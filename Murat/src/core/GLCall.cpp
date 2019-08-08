#include "GLCall.hpp"


void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {

    }
}

bool GLLogCall(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        spdlog::debug("[OpenGL Error]", error);
        spdlog::debug("Function: ", function);
        spdlog::debug("File: ", file);
        spdlog::debug("Line: ", line);
        return false;
    }
    return true;
}

