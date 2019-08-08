//
// Created by murat on 2019-08-08.
//

#pragma once

struct Window;

class Context {

public:
    explicit Context(GLFWwindow *windowHandle);

    void init();

    void swapBuffers();

private:

    GLFWwindow *m_WindowHandle;
};