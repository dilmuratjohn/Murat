#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLCall.hpp"
#include "Shader.hpp"
#include "Render.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "Texture.hpp"

//event
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float vertices[] = {
     // positions                  // colors           // texture coords
     0.50f,  0.50f, 1.00f, 1.00f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
     0.50f, -0.50f, 1.00f, 1.00f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 
    -0.50f, -0.50f, 1.00f, 1.00f,  0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
    -0.50f,  0.50f, 1.00f, 1.00f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f  
};
const unsigned int indices[] = {
     0, 1, 2,
     2, 3, 0,

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


    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //shader
    Shader shader("res/shader/Basic.shader");
    shader.bind();
    Texture texture2("res/pic/face.png", GL_RGB, GL_RGBA);
    Texture texture1("res/pic/wall.png", GL_RGB, GL_RGB);
    texture1.bind(0);
    texture2.bind(1);
    shader.setUniform1i("u_Texture0", 0);
    shader.setUniform1i("u_Texture1", 1);


    glm::mat4 transform = glm::mat4(1.0f);

    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, glm::vec3(0.5, 0.5, 0.5)); 


    shader.setUniformMat4f("transform", transform);


    //vertex
    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    IndexBuffer ib(indices, sizeof(indices));
    VertexBufferLayout layout;
    layout.push<float>(4);
    layout.push<float>(3);
    layout.push<float>(2);


    va.addBuffer(vb, layout);

    

    //key input
    glfwSetKeyCallback(window, key_callback);

    //loop
    while (!glfwWindowShouldClose(window))
    {

        Render::clear();
        Render::draw(va, ib, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //close window
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //polygon mode
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
