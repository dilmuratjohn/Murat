#pragma once

#include "GLCall.hpp"

class FrameBuffer
{
private:
    unsigned int m_RendererID;

public:
    FrameBuffer();
    ~FrameBuffer();

    void bufferTexture2D(unsigned int attachment, unsigned int buffer, unsigned int level);
    void bufferRenderBuffer(unsigned int attchment, unsigned int buffer);
    void bind() const;
    void unbind() const;
};