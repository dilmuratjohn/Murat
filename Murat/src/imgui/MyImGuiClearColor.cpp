#include "MyImGuiClearColor.hpp"

namespace MyImGui {

    MyImGuiClearColor::MyImGuiClearColor()
        : m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
    {
    }


    MyImGuiClearColor::~MyImGuiClearColor()
    {
    }

    void MyImGuiClearColor::OnUpdate(float deltaTime)
    {
    }

    void MyImGuiClearColor::OnRender()
    {
        GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
       
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }

    void MyImGuiClearColor::OnImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }

}