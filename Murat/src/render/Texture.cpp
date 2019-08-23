#include <glad/glad.h>
#include <core/Log.hpp>
#include "Texture.hpp"

namespace Murat {
    Texture2D::Texture2D(const std::string &filePath, bool transparency)
            :
            m_FilePath(filePath),
            m_RendererID(0),
            m_Transparency(transparency),
            m_LocalBuffer(nullptr),
            m_Width(0),
            m_Height(0),
            m_BPP(0) {
        m_InternalFormat = m_ImageFormat = m_Transparency ? GL_RGBA : GL_RGB;
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 0);

        if (!m_LocalBuffer)
            Log_Error("[Error] ", "Failed to load texture.");

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE,
                     m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);

        this->unbind();

        if (m_LocalBuffer)
            stbi_image_free(m_LocalBuffer);
    }

    Texture2D::~Texture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture2D::bind(unsigned int slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture2D::unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}