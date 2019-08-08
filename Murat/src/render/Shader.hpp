#pragma once

#include "Core.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>


struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
    std::string geometrySource;
};

class Shader {
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filePath);

    ~Shader();

    void bind() const;

    void unbind() const;

    void setUniform1i(const std::string &name, const int x);

    void setUniform1f(const std::string &name, const float x);

    void setUniform2f(const std::string &name, const float x, const float y);

    void setUniform2f(const std::string &name, const glm::vec2 &matrix);

    void setUniform3f(const std::string &name, const float x, const float y, const float z);

    void setUniform3f(const std::string &name, const glm::vec3 &matrix);

    void setUniform4f(const std::string &name, const float x, const float y, const float z, const float w);

    void setUniform4f(const std::string &name, const glm::vec4 &matrix);

    void setUniformMat2f(const std::string &name, const glm::mat2 &matrix);

    void setUniformMat3f(const std::string &name, const glm::mat3 &matrix);

    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix);

    inline unsigned int getId() { return m_RendererID; };

private:
    ShaderProgramSource parseShader(const std::string &filePath);

    unsigned int compileShader(unsigned int type, const std::string &source);

    unsigned int
    createShader(const std::string &vertexShader, const std::string &fragmentShader, const std::string &geometryShader);

    int getUniformLocation(const std::string &name);
};
