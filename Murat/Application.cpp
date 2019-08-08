#include "Murat.hpp"

#include <ctime>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
const float ASPECT_RATIO = (float) SCR_WIDTH / (float) SCR_HEIGHT;
const float NEAR_PLANE = 0.1f;
const float FAR_PLANE = 100.0f;
bool firstMouse = true;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

int main(int argc, char *argv[]) {

    spdlog::info("welcome to Murat Engine!");

    time_t now = time(0);
    char *TITLE = ctime(&now);

    Murat::WindowProps props = Murat::WindowProps("Murat Engine", SCR_WIDTH, SCR_HEIGHT);
    Murat::Window window = Murat::Window(props);

    glfwSetFramebufferSizeCallback(window.getWindow(), framebuffer_size_callback);
    // glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
    glfwSetScrollCallback(window.getWindow(), scroll_callback);
    glfwSetKeyCallback(window.getWindow(), key_callback);
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* transformation initialization */
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    /* shader */
    Shader shader_basic("res/shader/lighting_map.shader");
    Shader shader_color("res/shader/color.shader");
    Shader shader_texture("res/shader/texture.shader");

    Model imodel("res/model/heart.obj");


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
    const char *Version = "#version 330";
    ImGui_ImplOpenGL3_Init(Version);

    MyImGui::MyImGui *currentMyImGui = nullptr;
    MyImGui::MyImGuiMenu *myImGuiMenu = new MyImGui::MyImGuiMenu(currentMyImGui);
    currentMyImGui = myImGuiMenu;
    myImGuiMenu->RegisterMyImGui<MyImGui::MyImGuiClearColor>("clear color");
    /* loop */
    while (!glfwWindowShouldClose(window.getWindow())) {
        /* per-frame time logic */
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        projection = glm::perspective(glm::radians(camera.getFov()), ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
        view = camera.getViewMatrix();
        Render::clear();

        imodel.draw(shader_color);
        shader_color.setUniformMat4f("u_model", model);
        shader_color.setUniformMat4f("u_view", view);
        shader_color.setUniformMat4f("u_projection", projection);
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentMyImGui) {
            currentMyImGui->OnUpdate(0.0f);
            currentMyImGui->OnRender();
            ImGui::Begin("Test");
            if (currentMyImGui != myImGuiMenu && ImGui::Button("<-")) {
                delete currentMyImGui;
                currentMyImGui = myImGuiMenu;
            }
            currentMyImGui->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.onUpdate();
    }
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    /* close window */
    if (key == GLFW_KEY_ESCAPE && action != GLFW_RELEASE)
        glfwSetWindowShouldClose(window, true);

    /* polygon mode */
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* camera */
    if (key == GLFW_KEY_W && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (key == GLFW_KEY_S && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (key == GLFW_KEY_A && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::LEFT, deltaTime);
    if (key == GLFW_KEY_D && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (key == GLFW_KEY_UP && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::UP, deltaTime);
    if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE)
        camera.processKeyboard(Camera_Movement::DOWN, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
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

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.processMouseScroll(yoffset);
}
