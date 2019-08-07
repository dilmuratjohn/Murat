#include "FrameBuffer.hpp"

FrameBuffer::FrameBuffer()
{
    GLCall(glGenFramebuffers(1, &m_RendererID));
}

FrameBuffer::~FrameBuffer()
{
    GLCall(glDeleteFramebuffers(1, &m_RendererID));
}

void FrameBuffer::bufferTexture2D(unsigned int attachment, unsigned int buffer, unsigned int level)
{
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, buffer, level));
}

void FrameBuffer::bufferRenderBuffer(unsigned int attachment, unsigned int buffer)
{
    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buffer));
}

void FrameBuffer::bind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
}

void FrameBuffer::unbind() const
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}