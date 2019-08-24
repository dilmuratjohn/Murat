//
// Created by murat on 2019-08-09.
//

#ifndef M_KEY_EVENT_HPP
#define M_KEY_EVENT_HPP

#include "Event.hpp"
#include <muratpch.hpp>

namespace Murat {
    class KeyEvent : public Event {
    public:
        [[nodiscard]] inline unsigned int getKeyCode() const { return m_KeyCode; }

    protected:
        explicit KeyEvent(unsigned int keyCode)
                : m_KeyCode(keyCode) {}

        unsigned int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(unsigned int keyCode, int repeatCount)
                : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

        [[nodiscard]] inline int getRepeatCount() const { return m_RepeatCount; }

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

    private:
        int m_RepeatCount;

    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        explicit KeyReleasedEvent(unsigned int keyCode)
                : KeyEvent(keyCode) {}

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }
    };

    class KeyTypedEvent : public KeyEvent {
    public:
        explicit KeyTypedEvent(unsigned int keyCode)
                : KeyEvent(keyCode) {}

        [[nodiscard]] std::string toString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

    };
}

#endif


