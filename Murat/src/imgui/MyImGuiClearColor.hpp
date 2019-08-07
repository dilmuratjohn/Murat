#pragma once
#include "MyImGui.hpp"

namespace MyImGui {

    class MyImGuiClearColor : public MyImGui
    {
    public:
        MyImGuiClearColor();
        ~MyImGuiClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private: 
        float m_ClearColor[4];
    };
}