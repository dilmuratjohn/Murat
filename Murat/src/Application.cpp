//
// Created by murat on 2019-08-08.
//


#include "Application.hpp"
#include <core/Core.hpp>
#include <core/LayerStack.hpp>
#include <GLFW/glfw3.h>


namespace Murat {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application *Application::s_Instance = nullptr;

    Application::Application() {
        Log::init();
        ASSERT(!s_Instance, "Application already created.");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::create());
        m_Window->setEventCallback(BIND_EVENT_FN(onEvent));

        m_ImGuiLayer = new ImGuiLayer();
        pushOverlay(m_ImGuiLayer);
    }

    void Application::pushLayer(Layer *layer) {
        m_LayerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *layer) {
        m_LayerStack.pushOverlay(layer);
    }

    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);
        Log_Info(e.toString());
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

//        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
//        {
//            (*--it)->onEvent(e);
//            if (e.Handled)
//                break;
//        }
    }

    void Application::run() {
        while (m_Running) {
            double time = glfwGetTime();
            TimeStep timeStep(time - m_LastFrameTime);
            m_LastFrameTime = time;

//            for (Layer* layer : m_LayerStack)
//                layer->onUpdate(timeStep);

//            m_ImGuiLayer->begin();
//            for (Layer* layer : m_LayerStack)
//                layer->onImGuiRender();
//            m_ImGuiLayer->end();
            m_Window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    Application *create() {
        return new Application();
    }
}