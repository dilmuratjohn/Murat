#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "ResourceManager.hpp"


Shader ResourceManager::loadShader(const std::string& filePath, const std::string& name)
{
    Shaders[name] = Shader shader(filePath);
    return Shaders[name];
}
Shader ResourceManager::getShader(std::string& name)
{
    return Shaders[name];

}
Texture::Texture2D ResourceManager::loadTexture(const std::string& filePath, GLboolean alpha, std::string& name)
{
    Textures[name] = Texture::Texture2D(filePath, name);
    return Textures[name];
}
Texture::Texture2D ResourceManager::getTexture(std::string& name)
{
    return Textures[name];

}
void ResourceManager::clear()
{

    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);

    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}


#endif