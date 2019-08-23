//
// Created by murat on 2019-08-08.
//

#ifndef M_TIME_STEP_HPP
#define M_TIME_STEP_HPP

namespace Murat {

    class TimeStep {
    public:
        explicit TimeStep(float time = 0.0f)
                : m_Time(time) {
        }

        explicit operator float() const { return m_Time; }

        float getSeconds() const { return m_Time; }

        float getMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };

}

#endif


