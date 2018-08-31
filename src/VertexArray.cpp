#include "VertexArray.hpp"
#include "GLCall.hpp"


VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        std::cout<< element.count << std::endl;
        std::cout<< element.normalized << std::endl;
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, 9*sizeof(GLfloat)/*layout.getStride()*/, (const GLvoid *)offset));
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
void VertexArray::bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::unBind() const {
    GLCall(glBindVertexArray(0));
}