//
// Created by murat on 2019-08-09.
//

#ifndef M_EVENT_HPP
#define M_EVENT_HPP


#include <string>
#include <sstream>

namespace Murat {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory {
        None = 0,
        EventCategoryApplication,
        EventCategoryInput,
        EventCategoryKeyboard,
        EventCategoryMouse,
        EventCategoryMouseButton
    };


    class Event {
    public:
        bool Handled = false;

        inline virtual EventType getType() { return m_EventType; };

        inline virtual EventCategory getCategory() { return m_EventCategory; };

        inline virtual std::string toString() const = 0;

    protected:
        EventType m_EventType;
        EventCategory m_EventCategory;
    };


    class EventDispatcher {
        template<typename T>
        using EventFn = std::function<bool(T &)>;
    public:
        EventDispatcher(Event &event)
                : m_Event(event) {
        }

        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (m_Event.getType() == T::getStaticType()) {
                m_Event.Handled = func(*(T *) &m_Event);
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.toString();
    }


    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
                : m_Width(width), m_Height(height) {
            m_EventCategory = EventCategory::EventCategoryApplication;
            m_EventType = EventType::WindowResize;
        }

        inline unsigned int getWidth() const { return m_Width; }

        inline unsigned int getHeight() const { return m_Height; }

        static EventType getStaticType() { return EventType::WindowResize; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

    private:
        unsigned int m_Width, m_Height;
    };


    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {
            m_EventCategory = EventCategory::EventCategoryApplication;
            m_EventType = EventType::WindowClose;
        };

        static EventType getStaticType() { return EventType::WindowClose; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowCloseEvent: ";
            return ss.str();
        }
    };

    class AppTickEvent : public Event {
    public:
        AppTickEvent() {
            m_EventCategory = EventCategory::EventCategoryApplication;
            m_EventType = EventType::AppTick;
        }

        static EventType getStaticType() { return EventType::AppTick; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "AppTickEvent: ";
            return ss.str();
        }
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {
            m_EventCategory = EventCategory::EventCategoryApplication;
            m_EventType = EventType::AppUpdate;
        }

        static EventType getStaticType() { return EventType::AppUpdate; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "AppUpdateEvent: ";
            return ss.str();
        }
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {
            m_EventCategory = EventCategory::EventCategoryApplication;
            m_EventType = EventType::AppRender;
        }

        static EventType getStaticType() { return EventType::AppRender; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "AppRenderEvent: ";
            return ss.str();
        }
    };

}

#endif



