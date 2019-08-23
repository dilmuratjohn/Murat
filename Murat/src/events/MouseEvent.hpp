//
// Created by murat on 2019-08-09.
//

#ifndef M_MOUSE_EVENT_HPP
#define M_MOUSE_EVENT_HPP

#include "Event.hpp"
#include <string>
#include <sstream>

namespace Murat {
    class MouseMovedEvent : public Event {
    public:

        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {
            m_EventCategory = EventCategory::EventCategoryMouse;
            m_EventType = EventType::MouseMoved;
        }

        inline float getX() const { return m_MouseX; }

        inline float getY() const { return m_MouseY; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

    private:
        float m_MouseX, m_MouseY;
    };

    class MouseScrolledEvent : public Event {
    public:

        MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {
            m_EventCategory = EventCategory::EventCategoryMouse;
            m_EventType = EventType::MouseScrolled;
        }

        inline float getXOffset() const { return m_XOffset; }

        inline float getYOffset() const { return m_YOffset; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
            return ss.str();
        }

    private:
        float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event {
    public:

        inline int getMouseButton() const { return m_Button; }

    protected:

        explicit MouseButtonEvent(int button) : m_Button(button) {
            m_EventCategory = EventCategory::EventCategoryMouseButton;
            m_EventType = EventType::None;
        }

        int m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:

        explicit MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {
            m_EventCategory = EventCategory::EventCategoryMouseButton;
            m_EventType = EventType::MouseButtonPressed;
        }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:

        explicit MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {
            m_EventCategory = EventCategory::EventCategoryMouseButton;
            m_EventType = EventType::MouseButtonReleased;
        }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

    };


}

#endif
