//
// Created by murat on 2019-08-08.
//
#include "Murat.hpp"
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"
#include <functional>
#include <vector>

#pragma once

namespace Murat {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer() override = default;

        void onAttach() override;

        void onDetach() override;

        void onImGuiRender() override;

        void begin();

        void end();

    private:
        float m_Time = 0.0f;
    };
}


