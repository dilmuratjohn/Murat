#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//settings
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.7f, 0.2f, 1.0f);\n"
    "}\n\0";

const float position[] = {
     0.0f, -0.5f,  // bottom center
     0.5f,  0.5f,  // top right
    -0.5f,  0.5f   // top left
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Thu Aug 30 2018", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //shader
    int status;
    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);

    if(GL_FALSE == status){
        int length;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
        char* info = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(vs, length, &length, info);

        std::cout << "Failed to compile vertex shader" << std::endl;
        std::cout << info << std::endl;
    }

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);

    if(GL_FALSE == status){
        int length;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
        char* info = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(fs, length, &length, info);

        std::cout << "Failed to compile fragment shader" << std::endl;
        std::cout << info << std::endl;
    }

    //program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if(GL_FALSE == status) {
        int length;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &length);
        char* info = (char*)alloca(length * sizeof(char));
        glGetProgramInfoLog(shaderProgram, 512, NULL, info);
        std::cout << "Failed to compile shader program" << std::endl;
        std::cout << info << std::endl;
    }

    glValidateProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vs);
    glDeleteShader(fs);

    //vertex 
    unsigned int va; 
    unsigned int vb;
    glGenVertexArrays(1, &va);
    glGenBuffers(1, &vb);
    glBindVertexArray(va);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
