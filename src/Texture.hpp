#ifndef Texture_hpp
#define Texture_hpp

#include "GLCall.hpp"


class Texture
{
private:
    std::string    m_FilePath;
    unsigned int   m_RendererID;
    unsigned int   m_InternalFormat;
    unsigned int   m_ImageFormat;
    unsigned char* m_LocalBuffer;
    int            m_Width,
                   m_Height,
                   m_BPP;

public:
    Texture(const std::string& filePath, unsigned int internalFormat, unsigned int imageFormat);
    ~Texture();

    void bind(unsigned int solt = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }
};






















#endif