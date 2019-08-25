#ifndef M_VERTEX_BUFFER_LAYOUT_HPP
#define M_VERTEX_BUFFER_LAYOUT_HPP

#include <glad/glad.h>
#include <muratpch.hpp>


namespace Murat {
    struct VertexBufferElement {
        unsigned int count;
        unsigned int type;
        unsigned char normalized;

        static unsigned int getSizeOfType(unsigned int type) {
            switch (type) {
                case GL_FLOAT:
                    return sizeof(GLfloat);
                case GL_UNSIGNED_INT:
                    return sizeof(GLuint);
                case GL_UNSIGNED_BYTE:
                    return sizeof(GLubyte);

                default:
                    assert(false);
            }
            return 0;
        }
    };

    class VertexBufferLayout {

    public:
        VertexBufferLayout();

        ~VertexBufferLayout() = default;

        template<typename T>
        void push(unsigned int count);

        [[nodiscard]] inline std::vector<VertexBufferElement> getElements() const { return m_Elements; }

        [[nodiscard]] inline unsigned int getStride() const { return m_Stride; }

    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    };
}

#endif
