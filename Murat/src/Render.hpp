#pragma once

#include "FrameBuffer.hpp"
#include "RenderBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

namespace Render
{
    void clear();
    void clear(const char color);
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    void draw(const FrameBuffer& fb, const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
}
