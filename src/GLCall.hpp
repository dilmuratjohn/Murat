#ifndef GLCall_hpp
#define GLCall_hpp

#include <iostream>

#include <glad/glad.h>


#ifdef _WIN32
#define ASSERT(function) if (!(function)) __debugbreak();
#elif __APPLE__
#define ASSERT(function) if (!(function)) std::cin.get();
#endif

#define GLCall(function) GLClearError(); function; ASSERT(GLLogCall(#function, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#endif