#include "stb_image/stb_image.hpp"

#include "Texture.hpp"


Texture::Texture2D::Texture2D(const std::string& filePath, unsigned int internalFormat, unsigned int imageFormat)
    :
    m_FilePath(filePath),
    m_RendererID(0),
    m_InternalFormat(internalFormat),
    m_ImageFormat(imageFormat),
    m_LocalBuffer(nullptr),
    m_Width(0),
    m_Height(0),
    m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);

    if (!m_LocalBuffer)
        std::cout << "[Error] " << "Failed to load texture." << std::endl;

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, m_LocalBuffer));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    this -> unbind();

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::Texture2D::~Texture2D()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Texture2D::bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
void Texture::Texture2D::unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}