#pragma once

#include "render/VertexBuffer.hpp"
#include "render/VertexBufferLayout.hpp"

class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const;
};
