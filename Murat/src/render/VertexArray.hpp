#ifndef M_VERTEX_ARRAY_HPP
#define M_VERTEX_ARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "IndexBuffer.hpp"

namespace Murat {
    class VertexArray {

    public:
        VertexArray();

        ~VertexArray();

        void addVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer);

        void setIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer);

        inline const std::vector<std::shared_ptr<VertexBuffer>> &getVertexBuffers() { return m_VertexBuffers; };

        inline const std::shared_ptr<IndexBuffer> &getIndexBuffer() { return m_IndexBuffer; };

        void bind() const;

        void unbind() const;

    private:
        unsigned int m_RendererID = 0;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_IndexBuffer;
    };
}

#endif
