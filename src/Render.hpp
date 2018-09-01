#ifndef Render_hpp
#define Render_hpp

#include <iostream>

#include <glad/glad.h>

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "GLCall.hpp"


namespace Render
{
    void clear();
    void clear(const char color);
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
}









#endif