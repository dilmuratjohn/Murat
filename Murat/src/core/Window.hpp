//
// Created by murat on 2019-08-08.
//

#ifndef M_WINDOW_HPP
#define M_WINDOW_HPP

#include <events/Event.hpp>
#include <utility>
#include <string>

struct GLFWwindow;

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

        using EventCallback = std::function<void(Event & )>;

        explicit Window(const WindowProps &props);

        virtual ~Window();

        void onUpdate();

        inline unsigned int getWidth() const { return m_Data.width; }

        inline unsigned int getHeight() const { return m_Data.height; }


        static Window *create(const WindowProps &prop = WindowProps());

        inline void setEventCallback(const EventCallback &callback) { m_Data.eventCallback = callback; }

        void setVSync(bool enabled);

        bool isVSync() const;

        inline virtual GLFWwindow *getWindow() const { return m_Window; }

    private:
        virtual void init(const WindowProps &props);

        virtual void shutdown();

    private:
        GLFWwindow *m_Window{};

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync;
            EventCallback eventCallback;
        };

        WindowData m_Data;
    };
};

#endif
