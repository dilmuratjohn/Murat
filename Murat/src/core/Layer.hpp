//
// Created by murat on 2019-08-08.
//

#pragma once

#include <events/Event.hpp>
#include <string>
#include "TimeStep.hpp"

namespace Murat {

    class Layer {
    public:
        explicit Layer(const std::string &name = "Layer");

        virtual ~Layer() = default;

        virtual void onAttach() { };

        virtual void onDetach() { };

        virtual void onUpdate(TimeStep ts) { };

        virtual void onImGuiRender() { };

        virtual void onEvent(Event &event) { };


        inline const std::string &getName() const { return m_Name; };

    private:
        const std::string &m_Name;
    };

}