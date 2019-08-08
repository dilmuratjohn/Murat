//
// Created by murat on 2019-08-08.
//

#pragma once


namespace Murat {

    class TimeStep {
    public:
        TimeStep(float time = 0.0f)
                : m_Time(time) {
        }

        operator float() const { return m_Time; }

        float getSeconds() const { return m_Time; }

        float getMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };

}


