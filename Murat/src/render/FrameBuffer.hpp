#ifndef M_FRAMEBUFFER_HPP
#define M_FRAMEBUFFER_HPP

namespace Murat {
    class FrameBuffer {

    public:
        FrameBuffer();

        ~FrameBuffer();

        void bufferTexture2D(unsigned int attachment, unsigned int buffer, unsigned int level);

        void bufferRenderBuffer(unsigned int attachment, unsigned int buffer);

        void bind() const;

        void unbind() const;

    private:
        unsigned int m_RendererID = 0;
    };

}

#endif