#ifndef M_INDEX_BUFFER_HPP
#define M_INDEX_BUFFER_HPP

namespace Murat {
    class IndexBuffer {


    public:
        IndexBuffer(const unsigned int *data, unsigned int count);

        ~IndexBuffer();

        void bind() const;

        void unbind() const;

        [[nodiscard]] inline unsigned int getCount() const { return m_Count; }

    private:
        unsigned int m_RendererID = 0;
        unsigned int m_Count;
    };
}

#endif
