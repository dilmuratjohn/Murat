//
// Created by murat on 2019-08-08.
//

#include <events/Event.hpp>
#include <Window.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <events/KeyEvent.hpp>
#include <events/MouseEvent.hpp>
#include "Core.hpp"

namespace Murat {

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char *description) {
        Log_Error("GLFW Error ({0}): {1}", error, description);
    }

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
        m_Data.title = props.title;
        m_Data.width = props.width;
        m_Data.height = props.height;

        Log_Info("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();
            ASSERT(success, "Could not initialize GLFW.");
            s_GLFWInitialized = true;
        }


        m_Window = glfwCreateWindow((int) props.width, (int) props.height, m_Data.title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        setVSync(true);

        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        ASSERT(status, "Failed to load Glad.");
        spdlog::info("OpenGL Info:");
        spdlog::info("  Vendor: {0}", glGetString(GL_VENDOR));
        spdlog::info("  Renderer: {0}", glGetString(GL_RENDERER));
        spdlog::info("  Version: {0}", glGetString(GL_VERSION));


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            Log_Info("glfwSetWindowSizeCallback");
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.width = width;
            data.height = height;
            WindowResizeEvent event(width, height);
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scanCode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
                default:;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keyCode) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keyCode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                default: ;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float) xPos, (float) yPos);
            data.eventCallback(event);
        });
    }

    void Window::shutdown() {
        glfwDestroyWindow(m_Window);
    }

    void Window::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::setVSync(bool enabled) {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.vSync = enabled;
    }

    bool Window::isVSync() const {
        return m_Data.vSync;
    }

}