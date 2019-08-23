#include "VertexBufferLayout.hpp"

namespace Murat {
    VertexBufferLayout::VertexBufferLayout()
            : m_Stride(0) {}

    VertexBufferLayout::~VertexBufferLayout() {}

    template<>
    void VertexBufferLayout::push<float>(unsigned int count) {
        m_Elements.push_back({count, GL_FLOAT, GL_FALSE});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    void VertexBufferLayout::push<unsigned int>(unsigned int count) {
        m_Elements.push_back({count, GL_UNSIGNED_INT, GL_FALSE});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void VertexBufferLayout::push<unsigned char>(unsigned int count) {
        m_Elements.push_back({count, GL_UNSIGNED_BYTE, GL_FALSE});
        m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }
}