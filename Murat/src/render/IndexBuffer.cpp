#include <glad/glad.h>
#include "IndexBuffer.hpp"

namespace Murat {
    IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
            : m_Count(count) {
        static_assert(sizeof(unsigned int) == sizeof(GLuint), "index buffer type is not correct.");

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}