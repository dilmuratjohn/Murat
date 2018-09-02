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
#include "Camera.hpp"

/* event */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/* settings */
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
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

/* timing */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* camera */
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));


int main()
{
    /* glfw: initialize and configure */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    /* glfw window creation */
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Sat Sep 1 2018", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* glfw settings */
    glfwMakeContextCurrent(window);

    /* glad: load all OpenGL function pointers */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* window settings */
    GLCall(glfwSetFramebufferSizeCallback(window, framebuffer_size_callback));
    GLCall(glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED));
    GLCall(glfwSetCursorPosCallback(window, mouse_callback));
    GLCall(glfwSetScrollCallback(window, scroll_callback));
    GLCall(glfwSetKeyCallback(window, key_callback));
    GLCall(glfwSwapInterval(1));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    /* shader */
    Shader shader("res/shader/Basic.shader");
    shader.bind();
    Texture::Texture2D wall("res/pic/wall.png", false);
    wall.bind(0);
    shader.setUniform1i("u_Texture_wall", 0);

    /* vertex */
    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    VertexBufferLayout layout;
    layout.push<float>(4);
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    /* transformation initialization */
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::vec3 cubePositions[] =
    {
        glm::vec3( -1.0f,  0.0f,  0.0f),
        glm::vec3( -2.0f,  0.0f,  0.0f),
        glm::vec3( -3.0f,  0.0f,  0.0f),
        glm::vec3( -4.0f,  0.0f,  0.0f),
        glm::vec3( -5.0f,  0.0f,  0.0f),
        glm::vec3( -6.0f,  0.0f,  0.0f),
        glm::vec3( -7.0f,  0.0f,  0.0f),
        glm::vec3( -8.0f,  0.0f,  0.0f),
        glm::vec3( -9.0f,  0.0f,  0.0f),
        glm::vec3(  0.0f,  0.0f,  0.0f),
        glm::vec3(  1.0f,  0.0f,  0.0f),
        glm::vec3(  2.0f,  0.0f,  0.0f),
        glm::vec3(  3.0f,  0.0f,  0.0f),
        glm::vec3(  4.0f,  0.0f,  0.0f),
        glm::vec3(  5.0f,  0.0f,  0.0f),
        glm::vec3(  6.0f,  0.0f,  0.0f),
        glm::vec3(  7.0f,  0.0f,  0.0f),
        glm::vec3(  8.0f,  0.0f,  0.0f),
        glm::vec3(  9.0f,  0.0f,  0.0f),
        glm::vec3( -1.0f,  1.0f,  0.0f),
        glm::vec3( -2.0f,  1.0f,  0.0f),
        glm::vec3( -3.0f,  1.0f,  0.0f),
        glm::vec3( -4.0f,  1.0f,  0.0f),
        glm::vec3( -5.0f,  1.0f,  0.0f),
        glm::vec3( -6.0f,  1.0f,  0.0f),
        glm::vec3( -7.0f,  1.0f,  0.0f),
        glm::vec3( -8.0f,  1.0f,  0.0f),
        glm::vec3( -9.0f,  1.0f,  0.0f),
        glm::vec3(  0.0f,  1.0f,  0.0f),
        glm::vec3(  1.0f,  1.0f,  0.0f),
        glm::vec3(  2.0f,  1.0f,  0.0f),
        glm::vec3(  3.0f,  1.0f,  0.0f),
        glm::vec3(  4.0f,  1.0f,  0.0f),
        glm::vec3(  5.0f,  1.0f,  0.0f),
        glm::vec3(  6.0f,  1.0f,  0.0f),
        glm::vec3(  7.0f,  1.0f,  0.0f),
        glm::vec3(  8.0f,  1.0f,  0.0f),
        glm::vec3(  9.0f,  1.0f,  0.0f),
    };

    /* loop */
    while (!glfwWindowShouldClose(window))
    {
        /* per-frame time logic */
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* pass projection matrix to shader (note that in this case it could change every frame) */
        projection = glm::perspective(glm::radians(camera.getFov()), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.getViewMatrix();

        Render::clear();

        for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(cubePositions[0]); i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
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
    /* close window */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    /* polygon mode */
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* camera */
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::UP, deltaTime);
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        camera.processKeyboard(Camera_Movement::DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    /* reversed since y-coordinates go from bottom to top */
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(yoffset);
}
