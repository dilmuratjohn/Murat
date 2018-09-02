#ifndef Renderer_hpp
#define Renderer_hpp

#include <string>
#include <unordered_map>

#include <glad/glad.h>

#include "glm/glm.hpp"

#include "GLCall.hpp"

struct ShaderProgramSource
{
    std::string vertexSource;
    std::string fragmentSource;
    std::string geometrySource;
};

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& filePath);
    ~Shader();

    void bind() const;
    void unbind() const;
    void setUniform1i(const std::string& name, int x);
    void setUniform1f(const std::string& name, float x);
    void setUniform2f(const std::string& name, float x, float y);
    void setUniform2f(const std::string& name, const glm::vec2 &matrix);
    void setUniform3f(const std::string& name, float x, float y, float z);
    void setUniform3f(const std::string& name, const glm::vec3 &matrix);
    void setUniform4f(const std::string& name, float x, float y, float z, float w);
    void setUniform4f(const std::string& name, const glm::vec4 &matrix);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    ShaderProgramSource parseShader(const std::string& filePath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
    int getUniformLocation(const std::string& name);
};

#endif