#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "Texture.hpp"
#include "Shader.hpp"


namespace ResourceManager
{
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture::Texture2D> Textures;
    Shader loadShader(const std::string& filePath, const std::string name);
    Shader getShader(std::string name);
    Texture::Texture2D loadTexture(const std::string& filePath, std::string name, bool transparency);
    Texture::Texture2D getTexture(std::string name);
    void clear();
};

#endif