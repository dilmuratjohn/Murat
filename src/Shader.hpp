#ifndef Renderer_hpp
#define Renderer_hpp

#include <glad/glad.h>

#include <string>
#include <unordered_map>

#include "GLCall.hpp"

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
public:
    Shader(const std::string& filePath);
    ~Shader();

    void bind() const;
    void unBind() const;
private:
    ShaderProgramSource parseShader(const std::string& filePath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
};

#endif