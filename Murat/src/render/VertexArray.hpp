#ifndef M_VERTEX_ARRAY_HPP
#define M_VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace Murat {
    class VertexArray {
    private:
        unsigned int m_RendererID;

    public:
        VertexArray();

        ~VertexArray();

        void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);

        void bind() const;

        void unbind() const;
    };
}

#endif
