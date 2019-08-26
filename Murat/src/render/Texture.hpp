#ifndef M_TEXTURE_HPP
#define M_TEXTURE_HPP

#include <stb_image/stb_image.hpp>
#include <muratpch.hpp>
#include <core/Core.hpp>

namespace Murat {

    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        virtual void bind(unsigned int slot = 0) const = 0;
    };


    class Texture2D : public Texture {
    private:
        std::string     m_FilePath;
        unsigned int    m_RendererID;
        unsigned int    m_InternalFormat;
        unsigned int    m_ImageFormat;
        unsigned char * m_LocalBuffer;
        int             m_Width,
                        m_Height,
                        m_Channels;

    public:

        inline static Ref<Texture2D> create(const std::string& path) { return std::make_shared<Texture2D>(path); };

        Texture2D(const std::string &filePath);

        ~Texture2D();

        void bind(unsigned int slot = 0) const override;

        [[nodiscard]] inline unsigned int getWidth() const override { return m_Width; }

        [[nodiscard]] inline unsigned int getHeight() const override  { return m_Height; }

        inline unsigned int getId() { return m_RendererID; };
    };

}

#endif
