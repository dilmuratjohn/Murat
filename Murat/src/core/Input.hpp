//
// Created by murat on 2019-08-09.
//

#pragma once


#include <utility>

namespace Murat {
    class Input {
    public:

        static bool isKeyPressed(int keyCode);

        static bool isMouseButtonPressed(int button);

        static std::pair<float, float> getMousePosition();

        static float getMouseX();

        static float getMouseY();
    };
}


