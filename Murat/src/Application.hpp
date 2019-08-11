//
// Created by murat on 2019-08-08.
//
#pragma once

#include <core/Window.hpp>
#include <events/Event.hpp>
#include <core/LayerStack.hpp>
#include <imgui/ImGuiLayer.hpp>

namespace Murat {
    class Application {
    public:
        Application();

        virtual ~Application() = default;

        void run();

        void onEvent(Event &e);

        void pushLayer(Layer *layer);

        void pushOverlay(Layer *layer);

        inline Window &getWindow() { return *m_Window; }

        inline static Application &get() { return *s_Instance; }

    private:
        bool onWindowClose(WindowCloseEvent &e);

    private:
        std::unique_ptr <Window> m_Window;
        ImGuiLayer *m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;
        double m_LastFrameTime = 0.0f;
    private:
        static Application *s_Instance;
    };

    Application *create();
}


