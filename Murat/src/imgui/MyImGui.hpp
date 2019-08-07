#pragma once
#include "Render.hpp"
#include <functional>
#include <vector>

namespace MyImGui {
    class MyImGui
    {
    public:
        MyImGui() {};
        virtual ~MyImGui() {};

        virtual void OnUpdate(float deltaTime){}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class MyImGuiMenu :public MyImGui{
    public:
        MyImGuiMenu(MyImGui*& currentMyImGuiPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterMyImGui(const std::string& name) {
            m_MyImGuis.push_back(std::make_pair(name, []() {return new T(); }));
        }
    private:
        MyImGui*& m_CurrentMyImGui;
        std::vector<std::pair<std::string, std::function<MyImGui*()>>> m_MyImGuis;
    };
}
