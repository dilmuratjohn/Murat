//
// Created by murat on 2019-08-08.
//

#ifndef M_LAYER_HPP
#define M_LAYER_HPP

#include <events/Event.hpp>
#include <muratpch.hpp>
#include "TimeStep.hpp"

namespace Murat {

    class Layer {
    public:
        explicit Layer(const std::string &name = "Layer");

        virtual ~Layer() = default;

        virtual void onAttach() = 0;

        virtual void onDetach() = 0;

        virtual void onUpdate(TimeStep ts) = 0;

        virtual void onImGuiRender() = 0;

        virtual void onEvent(Event &event) = 0;


        [[nodiscard]] inline const std::string &getName() const { return m_Name; };

    private:
        const std::string &m_Name;
    };

}

#endif