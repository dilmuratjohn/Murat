#ifndef Texture_hpp
#define Texture_hpp

#include "GLCall.hpp"


class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path, GLint internalFormat, GLenum format);
    ~Texture();

    void bind(unsigned int solt = 0) const;
    void unbind() const;

    inline int getWidth() const { return m_Width; }
    inline int getHeight() const { return m_Height; }
};






















#endif