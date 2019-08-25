#ifndef M_VERTEX_BUFFER_HPP
#define M_VERTEX_BUFFER_HPP

#include "VertexBufferLayout.hpp"

namespace Murat {
    class VertexBuffer {

    public:
        VertexBuffer(const void *data, unsigned int size);

        ~VertexBuffer();

        void bind() const;

        void unbind() const;

        [[nodiscard]] const VertexBufferLayout &getLayout() const { return m_Layout; }

        void setLayout(const VertexBufferLayout &layout) { m_Layout = layout; }

    private:
        unsigned int m_RendererID = 0;
        VertexBufferLayout m_Layout;
    };
}

#endif
