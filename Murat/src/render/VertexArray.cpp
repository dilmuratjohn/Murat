#include "VertexArray.hpp"

namespace Murat {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_RendererID);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void VertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
        bind();
        vertexBuffer->bind();
        const auto &elements = vertexBuffer->getLayout().getElements();
        std::size_t offset = 0;
        int index = 0;
        for (VertexBufferElement element : elements) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.count, element.type, element.normalized,
                                  vertexBuffer->getLayout().getStride(), (GLvoid *) offset);
            offset += element.count * VertexBufferElement::getSizeOfType(element.type);
            index++;
        }
    }

    void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->bind();

        m_IndexBuffer = indexBuffer;
    }

    void VertexArray::bind() const {
        glBindVertexArray(m_RendererID);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }
}