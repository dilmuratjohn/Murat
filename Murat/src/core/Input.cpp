//
// Created by murat on 2019-08-09.
//

#include <glfw/include/GLFW/glfw3.h>
#include <Application.hpp>
#include "Input.hpp"

namespace Murat {

    bool Input::isKeyPressed(int keyCode) {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getWindow());
        auto state = glfwGetKey(window, keyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::isMouseButtonPressed(int button) {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::getMousePosition() {
        auto window = static_cast<GLFWwindow *>(Application::get().getWindow().getWindow());
        double positionX, positionY;
        glfwGetCursorPos(window, &positionX, &positionY);

        return {(float) positionX, (float) positionY};
    }

    float Input::getMouseX() {
        auto[x, y] = getMousePosition();
        return x;
    }

    float Input::getMouseY() {
        auto[x, y] = getMousePosition();
        return y;
    }

}