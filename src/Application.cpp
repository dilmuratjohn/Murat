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
const char * TITLE = "Sun Sep 2 2018";
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;
const float ASPECT_RATIO = (float)SCR_WIDTH / (float)SCR_HEIGHT;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;

const float vertices_cube[] =
    /* Position  [X.Y.Z.W]      Color  [R.G.B.A]             TexCoord  [S.T]   Normal  [X.Y.Z.W]  */
{
    -0.5f, -0.5f, -0.5f, 1.00f, 1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 0.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 0.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.00f,   0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 1.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.00f,   1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 1.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 1.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.00f, 0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 0.0f,       0.0f, 0.0f, -1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.00f,  1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 1.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.00f,  0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 0.0f,       0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.00f,   1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 0.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 1.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.00f, 0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 1.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.00f, 1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 1.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 0.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.00f,   0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 0.0f,       -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 1.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.00f,  0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 1.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.00f,  1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 1.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 0.0f,       1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.00f, 1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 1.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 1.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.00f,   0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 0.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.00f,   1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 0.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 1.00f,  0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 0.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.00f, 0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 1.0f,       0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.00f,  1.0f, 0.0f, 0.0f, 0.50f,     0.0f, 1.0f,       0.0f, 1.0f,  0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     1.0f, 1.0f,       0.0f, 1.0f,  0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    0.0f, 0.0f, 1.0f, 0.50f,     1.0f, 0.0f,       0.0f, 1.0f,  0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.00f,    1.0f, 0.0f, 0.0f, 0.50f,     1.0f, 0.0f,       0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.00f,   0.0f, 1.0f, 0.0f, 0.50f,     0.0f, 0.0f,       0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.00f,  0.0f, 0.0f, 1.0f, 0.50f,     0.0f, 1.0f,       0.0f, 1.0f,  0.0f, 1.0f
};


const float vertices_flat[] =
    /* Position  .X.Y.Z.W.        TexCoord .S.T. */
{
    0.50f,  0.50f, 1.00f, 1.00f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    0.50f, -0.50f, 1.00f, 1.00f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.50f, -0.50f, 1.00f, 1.00f,   0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.50f,  0.50f, 1.00f, 1.00f,   0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
};

const unsigned int indices_flat[] =
{
    0, 1, 2,
    2, 3, 0,
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, TITLE, NULL, NULL);

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
    Shader shader_basic("res/shader/basic.shader.c");
    Shader shader_color("res/shader/color.shader.c");
    Shader shader_texture("res/shader/texture.shader.c");


    /* texture */
    Texture::Texture2D wall("res/pic/wall.png", false);
    Texture::Texture2D floor("res/pic/floor.png", false);
    Texture::Texture2D box("res/pic/box.png", true);

    /* cube */
    VertexArray va_box;
    VertexBuffer vb_box(vertices_cube, sizeof(vertices_cube));
    VertexBufferLayout layout_box;
    layout_box.push<float>(4);
    layout_box.push<float>(4);
    layout_box.push<float>(2);
    layout_box.push<float>(4);

    /* squre */
    VertexArray va_floor;
    VertexBuffer vb_floor(vertices_flat, sizeof(vertices_flat));
    VertexBufferLayout layout_floor;
    IndexBuffer ib_floor(indices_flat, sizeof(indices_flat));
    layout_floor.push<float>(4);
    layout_floor.push<float>(2);
    layout_floor.push<float>(4);



    /* transformation initialization */
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::vec3 lightPosition(1.0f, 3.0f, 2.0f);
    glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 translatePositions[] =
    {
        // glm::vec3( -1.0f,  0.0f,  0.0f),
        // glm::vec3( -2.0f,  0.0f,  0.0f),
        // glm::vec3( -3.0f,  0.0f,  0.0f),
        // glm::vec3( -4.0f,  0.0f,  0.0f),
        // glm::vec3( -5.0f,  0.0f,  0.0f),
        // glm::vec3( -6.0f,  0.0f,  0.0f),
        // glm::vec3( -7.0f,  0.0f,  0.0f),
        // glm::vec3( -8.0f,  0.0f,  0.0f),
        // glm::vec3( -9.0f,  0.0f,  0.0f),
        // glm::vec3(  0.0f,  0.0f,  0.0f),
        // glm::vec3(  1.0f,  0.0f,  0.0f),
        // glm::vec3(  2.0f,  0.0f,  0.0f),
        // glm::vec3(  3.0f,  0.0f,  0.0f),
        // glm::vec3(  4.0f,  0.0f,  0.0f),
        // glm::vec3(  5.0f,  0.0f,  0.0f),
        // glm::vec3(  6.0f,  0.0f,  0.0f),
        // glm::vec3(  7.0f,  0.0f,  0.0f),
        // glm::vec3(  8.0f,  0.0f,  0.0f),
        // glm::vec3(  9.0f,  0.0f,  0.0f),
        // glm::vec3( -1.0f,  1.0f,  0.0f),
        // glm::vec3( -2.0f,  1.0f,  0.0f),
        // glm::vec3( -3.0f,  1.0f,  0.0f),
        // glm::vec3( -4.0f,  1.0f,  0.0f),
        // glm::vec3( -5.0f,  1.0f,  0.0f),
        // glm::vec3( -6.0f,  1.0f,  0.0f),
        // glm::vec3( -7.0f,  1.0f,  0.0f),
        // glm::vec3( -8.0f,  1.0f,  0.0f),
        // glm::vec3( -9.0f,  1.0f,  0.0f),
        // glm::vec3(  0.0f,  1.0f,  0.0f),
        // glm::vec3(  1.0f,  1.0f,  0.0f),
        glm::vec3(  2.0f,  1.0f,  0.0f),
        // glm::vec3(  3.0f,  1.0f,  0.0f),
        // glm::vec3(  4.0f,  1.0f,  0.0f),
        // glm::vec3(  5.0f,  1.0f,  0.0f),
        // glm::vec3(  6.0f,  1.0f,  0.0f),
        // glm::vec3(  7.0f,  1.0f,  0.0f),
        // glm::vec3(  8.0f,  1.0f,  0.0f),
        // glm::vec3(  9.0f,  1.0f,  0.0f),
        // glm::vec3( -1.0f,  2.0f,  0.0f),
        // glm::vec3( -2.0f,  2.0f,  0.0f),
        // glm::vec3( -3.0f,  2.0f,  0.0f),
        // glm::vec3( -4.0f,  2.0f,  0.0f),
        // glm::vec3( -5.0f,  2.0f,  0.0f),
        // glm::vec3( -6.0f,  2.0f,  0.0f),
        // glm::vec3( -7.0f,  2.0f,  0.0f),
        // glm::vec3( -8.0f,  2.0f,  0.0f),
        // glm::vec3( -9.0f,  2.0f,  0.0f),
        // glm::vec3(  0.0f,  2.0f,  0.0f),
        // glm::vec3(  1.0f,  2.0f,  0.0f),
        // glm::vec3(  2.0f,  2.0f,  0.0f),
        // glm::vec3(  3.0f,  2.0f,  0.0f),
        // glm::vec3(  4.0f,  2.0f,  0.0f),
        // glm::vec3(  5.0f,  2.0f,  0.0f),
        // glm::vec3(  6.0f,  2.0f,  0.0f),
        // glm::vec3(  7.0f,  2.0f,  0.0f),
        // glm::vec3(  8.0f,  2.0f,  0.0f),
        // glm::vec3(  9.0f,  2.0f,  0.0f),
    };


    /* loop */
    while (!glfwWindowShouldClose(window))
    {
        {
            /* per-frame time logic */
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            projection = glm::perspective(glm::radians(camera.getFov()), ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
            view = camera.getViewMatrix();

            Render::clear();

            /* lamp */
            {
                shader_color.bind();
                model = glm::mat4(1.0f);
                model = glm::translate(model, lightPosition);
                model = glm::scale(model, glm::vec3(0.1f));
                shader_color.setUniformMat4f("u_model", model);
                shader_color.setUniformMat4f("u_view", view);
                shader_color.setUniformMat4f("u_projection", projection);
                va_box.addBuffer(vb_box, layout_box);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            /* floor */
            // {
            //     shader_texture.bind();
            //     shader_texture.setUniform1i("u_Texture", 0);
            //     for (int i = 0; i < sizeof(translatePositions) / sizeof(translatePositions[0]); i++)
            //     {
            //         if (i == 38)
            //             break;
            //         model = glm::mat4(1.0f);
            //         model = glm::translate(model, translatePositions[i]);
            //         model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            //         model = glm::translate(model, glm::vec3(0.0f, -1.0f, -1.5001f));
            //         shader_texture.setUniformMat4f("u_model", model);
            //         shader_texture.setUniformMat4f("u_view", view);
            //         shader_texture.setUniformMat4f("u_projection", projection);
            //         shader_texture.setUniform4f("lightPosition", lightPosition.x, lightPosition.y, lightPosition.z, 1.0f);
            //         floor.bind();
            //         va_floor.addBuffer(vb_floor, layout_floor);
            //         Render::draw(va_floor, ib_floor, shader_texture);
            //     }
            // }

            /* box */
            {
                shader_basic.bind();
                shader_basic.setUniform1i("u_Texture", 0);
                for (unsigned int i = 0; i < sizeof(translatePositions) / sizeof(translatePositions[0]); i++)
                {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, translatePositions[i]);
                    shader_basic.setUniformMat4f("model", model);
                    shader_basic.setUniformMat4f("view", view);
                    shader_basic.setUniformMat4f("projection", projection);

                    shader_basic.setUniform4f("u_viewPosition", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z, 1.0f);

                    shader_basic.setUniform4f("u_light.ambient",  0.2f, 0.2f, 0.2f, 1.0f);
                    shader_basic.setUniform4f("u_light.diffuse",  0.5f, 0.5f, 0.5f, 1.0f);
                    shader_basic.setUniform4f("u_light.specular", 1.0f, 1.0f, 1.0f, 1.0f);
                    shader_basic.setUniform4f("u_light.position", lightPosition.x, lightPosition.y, lightPosition.z, 1.0f);

                    shader_basic.setUniform4f("u_material.ambient",  1.0f, 0.5f, 0.31f, 1.0f);
                    shader_basic.setUniform4f("u_material.diffuse",  1.0f, 0.5f, 0.31f, 1.0f);
                    shader_basic.setUniform4f("u_material.specular", 0.5f, 0.5f, 0.5f, 1.0f);
                    shader_basic.setUniform1f("u_material.shininess", 32.0f);

                    if (i % 2 == 0)
                        wall.bind(0);
                    else
                        box.bind(0);
                    va_box.addBuffer(vb_box, layout_box);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
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
