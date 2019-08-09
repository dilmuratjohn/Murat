#include "render/RenderBuffer.hpp"
#include <glad/glad.h>

RenderBuffer::RenderBuffer(unsigned int attachment, unsigned int width, unsigned int height) {
    glGenRenderbuffers(1, &m_RendererID);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
    glRenderbufferStorage(GL_RENDERBUFFER, attachment, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

RenderBuffer::~RenderBuffer() {
    glDeleteRenderbuffers(1, &m_RendererID);
}

void RenderBuffer::bind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
}

void RenderBuffer::unbind() const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}