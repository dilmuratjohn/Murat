#ifndef M_TEXTURE_HPP
#define M_TEXTURE_HPP

#include <stb_image/stb_image.hpp>
#include <muratpch.hpp>

namespace Murat {


    class Texture2D {
    private:
        std::string     m_FilePath;
        unsigned int    m_RendererID;
        bool            m_Transparency;
        unsigned int    m_InternalFormat;
        unsigned int    m_ImageFormat;
        unsigned char * m_LocalBuffer;
        int             m_Width,
                        m_Height,
                        m_BPP;

    public:
        Texture2D(const std::string &filePath, bool transparency);

        ~Texture2D();

        void bind(unsigned int slot = 0) const;

        void unbind() const;

        [[nodiscard]] inline int getWidth() const { return m_Width; }

        [[nodiscard]] inline int getHeight() const { return m_Height; }

        inline unsigned int getId() { return m_RendererID; };
    };

}

#endif
