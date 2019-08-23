#ifndef M_RENDER_BUFFER_HPP
#define M_RENDER_BUFFER_HPP

namespace Murat {
    class RenderBuffer {
    private:
        unsigned int m_RendererID;

    public:
        RenderBuffer(unsigned int attachment, unsigned int width, unsigned int height);

        ~RenderBuffer();

        void bind() const;

        void unbind() const;
    };
}

#endif
