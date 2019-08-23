#include <glad/glad.h>
#include "FrameBuffer.hpp"

namespace Murat {
    FrameBuffer::FrameBuffer() {
        glGenFramebuffers(1, &m_RendererID);
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &m_RendererID);
    }

    void FrameBuffer::bufferTexture2D(unsigned int attachment, unsigned int buffer, unsigned int level) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, buffer, level);
    }

    void FrameBuffer::bufferRenderBuffer(unsigned int attachment, unsigned int buffer) {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, buffer);
    }

    void FrameBuffer::bind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
    }

    void FrameBuffer::unbind() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}