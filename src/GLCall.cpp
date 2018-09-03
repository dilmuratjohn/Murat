#include <iostream>

#include "GLCall.hpp"


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR)
    {

    }
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] <" << error    << ">" << std::endl;
        std::cout << "Function:      <" << function << ">" << std::endl;
        std::cout << "File:          <" << file     << ">" << std::endl;
        std::cout << "Line:          <" << line     << ">" << std::endl;
        return false;
    }
    return true;
}

