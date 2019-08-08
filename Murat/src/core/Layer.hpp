//
// Created by murat on 2019-08-08.
//

#pragma once

#include <string>

namespace Murat {

    class Layer {
    public:
        explicit Layer(const std::string &name = "Layer");

        virtual ~Layer() = default;

        virtual void onAttach() = 0;

        virtual void onDetach() = 0;

        virtual void onUpdate();

        virtual void onImGuiRender() = 0;

        inline const std::string &getName() const { return m_Name; };

    private:
        const std::string &m_Name;
    };

}