//
// Created by murat on 2019-08-08.
//

#include <spdlog/include/spdlog/spdlog.h>
#include "Window.hpp"

namespace Murat {

    static bool s_GLFWInitialized = false;


    Window *Window::create(const WindowProps &props) {
        return new Window(props);
    }

    Window::Window(const WindowProps &props) {
        init(props);
    }

    Window::~Window() {
        shutdown();
    }

    void Window::init(const WindowProps &props) {
        m_Data.Title = props.title;
        m_Data.Width = props.width;
        m_Data.Height = props.height;

        spdlog::info("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            if (success == 0)
                spdlog::error("Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_Window = glfwCreateWindow((int) props.width, (int) props.height, m_Data.Title.c_str(), nullptr, nullptr);

        m_Context = new Context(m_Window);
        m_Context->init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

        });
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_Window);
    }

    void Window::onUpdate() {
        glfwPollEvents();
        m_Context->swapBuffers();
    }

    void Window::setVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool Window::isVSync() const {
        return m_Data.VSync;
    }

}