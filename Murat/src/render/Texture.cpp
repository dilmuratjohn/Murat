#include <glad/glad.h>
#include <core/Log.hpp>
#include "Texture.hpp"

namespace Murat {
    Texture2D::Texture2D(const std::string& filePath)
            :
            m_FilePath(filePath),
            m_RendererID(0),
            m_LocalBuffer(nullptr),
            m_Width(0),
            m_Height(0),
            m_Channels(0) {
        
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Channels, 0);

        if (!m_LocalBuffer)
            Log_Error("[Error] Failed to load texture.");

        if (m_Channels == 4)
        {
            m_InternalFormat = GL_RGBA8;
            m_ImageFormat = GL_RGBA;
        }
        else if (m_Channels == 3)
        {
            m_InternalFormat = GL_RGB8;
            m_ImageFormat = GL_RGB;
        }

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE,
                     m_LocalBuffer);
        glGenerateMipmap(GL_TEXTURE_2D);

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

}
