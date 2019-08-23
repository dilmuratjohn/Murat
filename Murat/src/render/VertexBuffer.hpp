#ifndef M_VERTEX_BUFFER_HPP
#define M_VERTEX_BUFFER_HPP

namespace Murat {
    class VertexBuffer {
    private:
        unsigned int m_RendererID;

    public:
        VertexBuffer(const void *data, unsigned int size);

        ~VertexBuffer();

        void bind() const;

        void unbind() const;
    };
}

#endif
