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

/* event */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

/* settings */
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

/* Timing */
float deltaTime = 0.0f;
float lastFrame = 0.0f;

/* camera */
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

bool firstMouse = true;
/* a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left. */
float yaw   = -90.0f;
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;




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
    GLCall(glfwSwapInterval(1));
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    /* shader */
    Shader shader("res/shader/Basic.shader");
    shader.bind();
    Texture texture2("res/pic/face.png", GL_RGB, GL_RGBA);
    Texture texture1("res/pic/wall.png", GL_RGB, GL_RGB);
    texture1.bind(0);
    texture2.bind(1);
    shader.setUniform1i("u_Texture0", 0);
    shader.setUniform1i("u_Texture1", 1);

    /* vertex */
    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices));
    //IndexBuffer ib(indices, sizeof(indices));
    VertexBufferLayout layout;
    layout.push<float>(4);
    layout.push<float>(3);
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    /* transformation */
    glm::mat4 transform = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(25.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), ((float)SCR_WIDTH / (float)SCR_HEIGHT), 0.1f, 100.0f);

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

    /* key input */
    glfwSetKeyCallback(window, key_callback);

    /* loop */
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        projection = glm::perspective(glm::radians(fov), ((float)SCR_WIDTH / (float)SCR_HEIGHT), 0.1f, 100.0f);

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
    float cameraSpeed = 2.5f * deltaTime;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

    /* reversed since y-coordinates go from bottom to top */
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    /* change this value to your liking */
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    /* make sure that when pitch is out of bounds, screen doesn't get flipped */
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (fov >= 1.0f && fov <= 65.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 65.0f)
        fov = 65.0f;
}
