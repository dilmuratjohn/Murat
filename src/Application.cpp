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
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

const float vertices[] =
{
    -0.5f, -0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.00f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.00f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.00f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f
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
    glfwSwapInterval(1);
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



    //vertex
    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    //IndexBuffer ib(indices, sizeof(indices));
    VertexBufferLayout layout;
    layout.push<float>(4);
    layout.push<float>(3);
    layout.push<float>(2);


    va.addBuffer(vb, layout);

    //transformation
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(25.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), ((float)SCR_WIDTH / (float)SCR_HEIGHT), 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST);
    //key input
    glfwSetKeyCallback(window, key_callback);

    glm::vec3 cubePositions[] =
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //loop
    while (!glfwWindowShouldClose(window))
    {

        Render::clear();
        for (unsigned int i = 0; i < 10; i++)
        {

            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

            transform = projection * view * model;

            shader.setUniformMat4f("transform", transform);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

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
