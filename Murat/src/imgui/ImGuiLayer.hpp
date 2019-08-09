//
// Created by murat on 2019-08-08.
//
#pragma once

#include <core/Layer.hpp>
#include <functional>
#include <vector>


namespace Murat {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();

        ~ImGuiLayer() override = default;

        void onAttach() override;

        void onDetach() override;

        void onUpdate(TimeStep ts) override ;

        void onImGuiRender() override;

        void begin();

        void end();

    private:
        float m_Time = 0.0f;
    };
}


