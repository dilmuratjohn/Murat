//
// Created by murat on 2019-08-08.
//

#pragma once

#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <render/Context.hpp>

namespace Murat {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        explicit WindowProps(std::string title = "Murat Engine", unsigned int width = 800, unsigned int height = 600) :
                title(std::move(title)), width(width), height(height) {

        }
    };

    class Window {

    public:
        Window(const WindowProps &props);

        virtual ~Window();

        void onUpdate();

        inline unsigned int getWidth() const { return m_Data.Width; }

        inline unsigned int getHeight() const { return m_Data.Height; }


        static Window *create(const WindowProps &prop = WindowProps());

        void setVSync(bool enabled);

        bool isVSync() const;

        inline virtual GLFWwindow *getWindow() const { return m_Window; }

    private:
        virtual void init(const WindowProps &props);

        virtual void shutdown();

    private:
        GLFWwindow *m_Window;
        Context *m_Context;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
        };

        WindowData m_Data;
    };
};
