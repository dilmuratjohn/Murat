#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.hpp"


Shader::Shader(const std::string& filePath)
    : m_RendererID(0), m_FilePath(filePath)
{
    ShaderProgramSource source = parseShader(filePath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource, source.geometrySource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
    };

    std::string line;
    std::stringstream ss[3];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
            if (line.find("geometry") != std::string::npos)
                type = ShaderType::GEOMETRY;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str(), ss[2].str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string & source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile <" << (type == GL_VERTEX_SHADER ? "Vetex" : "Fragment")
                  << " Shader>" << std::endl << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
    GLCall(unsigned int program = glCreateProgram());

    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    //GLCall(glAttachShader(program, gs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    GLCall(glDeleteShader(gs));

    return program;
}


void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform1i(const std::string& name, const int x)
{
    GLCall(glUniform1i(getUniformLocation(name), x));
}

void Shader::setUniform1f(const std::string& name, const float x)
{
    GLCall(glUniform1f(getUniformLocation(name), x));
}

void Shader::setUniform2f(const std::string& name, const float x, const float y)
{
    GLCall(glUniform2f(getUniformLocation(name), x, y));
}

void Shader::setUniform2f(const std::string& name, const glm::vec2 &matrix)
{
    GLCall(glUniform2f(getUniformLocation(name), matrix.x, matrix.y));
}

void Shader::setUniform3f(const std::string& name, const float x, const float y, const float z)
{
    GLCall(glUniform3f(getUniformLocation(name), x, y, z));
}

void Shader::setUniform3f(const std::string& name, const glm::vec3 &matrix)
{
    GLCall(glUniform3f(getUniformLocation(name), matrix.x, matrix.y, matrix.z));
}

void Shader::setUniform4f(const std::string& name, const float x, const float y, const float z, const float w)
{
    GLCall(glUniform4f(getUniformLocation(name), x, y, z, w));
}

void Shader::setUniform4f(const std::string& name, const glm::vec4 &matrix)
{
    GLCall(glUniform4f(getUniformLocation(name), matrix.x, matrix.y, matrix.z, matrix.w));
}

void Shader::setUniformMat2f(const std::string& name, const glm::mat2 &matrix)
{
    GLCall(glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniformMat3f(const std::string& name, const glm::mat3 &matrix)
{
    GLCall(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4 &matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "[Warring]: uniform <" << name << "> doesn't exist." << std::endl
                  << "[FilePath]: " << m_FilePath << std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}
