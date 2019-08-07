#include "MyImGui.hpp"

MyImGui::MyImGuiMenu::MyImGuiMenu(MyImGui *& currentMyImGuiPointer)
    : m_CurrentMyImGui(currentMyImGuiPointer)
{
}

void MyImGui::MyImGuiMenu::OnImGuiRender()
{
    for (auto& MyImGui : m_MyImGuis) {
        if (ImGui::Button(MyImGui.first.c_str()))
            m_CurrentMyImGui = MyImGui.second();
    }
}