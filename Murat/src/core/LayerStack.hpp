//
// Created by murat on 2019-08-09.
//

#ifndef M_LAYER_STACK_HPP
#define M_LAYER_STACK_HPP


#include "Layer.hpp"
#include <muratpch.hpp>

namespace Murat {
    class LayerStack {
    public:
        LayerStack();

        ~LayerStack();

        void pushLayer(Layer *layer);

        void pushOverlay(Layer *overlay);

        void popLayer(Layer *layer);

        void popOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }

        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}

#endif