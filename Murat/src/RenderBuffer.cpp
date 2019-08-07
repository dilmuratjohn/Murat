#include "RenderBuffer.hpp"

RenderBuffer::RenderBuffer(unsigned int attachment,unsigned int width, unsigned int height)
{
    GLCall(glGenRenderbuffers(1, &m_RendererID));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, attachment, width, height));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}

RenderBuffer::~RenderBuffer()
{
    GLCall(glDeleteRenderbuffers(1, &m_RendererID));
}

void RenderBuffer::bind() const
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID));
}

void RenderBuffer::unbind() const
{
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
}