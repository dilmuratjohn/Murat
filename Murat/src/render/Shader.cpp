#include <glad/glad.h>
#include <core/Log.hpp>
#include "Shader.hpp"

namespace Murat {
    Shader::Shader(const std::string &filePath)
            : m_RendererID(0) {
        ShaderProgramSource source = parseShader(filePath);
        m_RendererID = createShader(source.vertexSource, source.fragmentSource, source.geometrySource);
    }

    Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader,const std::string &geometryShader)
            : m_RendererID(0) {
        m_RendererID = createShader(vertexShader, fragmentShader, geometryShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_RendererID);
    }

    ShaderProgramSource Shader::parseShader(const std::string &filePath) {
        std::ifstream stream(filePath);

        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
        };

        std::string line;
        std::stringstream ss[3];

        ShaderType type = ShaderType::NONE;

        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
                if (line.find("geometry") != std::string::npos)
                    type = ShaderType::GEOMETRY;
            } else {
                ss[(int) type] << line << '\n';
            }
        }
        return {ss[0].str(), ss[1].str(), ss[2].str()};
    }

    unsigned int Shader::compileShader(unsigned int type, const std::string &source) {
        unsigned int id = glCreateShader(type);
        const char *src = source.c_str();

        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *) alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            Log_Info("Failed to compile <", (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment"), " Shader>\n", message);
            glDeleteShader(id);
            return 0;
        }
        return id;
    }

    unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader,
                                      const std::string &geometryShader) {
        unsigned int program = glCreateProgram();

        unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
//    unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        //glAttachShader(program, gs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);
//    glDeleteShader(gs);

        return program;
    }


    void Shader::bind() const {
        glUseProgram(m_RendererID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::setUniform1i(const std::string &name, const int x) {
        glUniform1i(getUniformLocation(name), x);
    }

    void Shader::setUniform1f(const std::string &name, const float x) {
        glUniform1f(getUniformLocation(name), x);
    }

    void Shader::setUniform2f(const std::string &name, const float x, const float y) {
        glUniform2f(getUniformLocation(name), x, y);
    }

    void Shader::setUniform2f(const std::string &name, const glm::vec2 &matrix) {
        glUniform2f(getUniformLocation(name), matrix.x, matrix.y);
    }

    void Shader::setUniform3f(const std::string &name, const float x, const float y, const float z) {
        glUniform3f(getUniformLocation(name), x, y, z);
    }

    void Shader::setUniform3f(const std::string &name, const glm::vec3 &matrix) {
        glUniform3f(getUniformLocation(name), matrix.x, matrix.y, matrix.z);
    }

    void Shader::setUniform4f(const std::string &name, const float x, const float y, const float z, const float w) {
        glUniform4f(getUniformLocation(name), x, y, z, w);
    }

    void Shader::setUniform4f(const std::string &name, const glm::vec4 &matrix) {
        glUniform4f(getUniformLocation(name), matrix.x, matrix.y, matrix.z, matrix.w);
    }

    void Shader::setUniformMat2f(const std::string &name, const glm::mat2 &matrix) {
        glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::setUniformMat3f(const std::string &name, const glm::mat3 &matrix) {
        glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    void Shader::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    int Shader::getUniformLocation(const std::string &name) {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        if (location == -1)
            Log_Error("uniform [{0}] doesn't exist.", name);
        m_UniformLocationCache[name] = location;
        return location;
    }
}
