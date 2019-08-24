//
// Created by murat on 2019-08-08.
//

#ifndef M_TIME_STEP_HPP
#define M_TIME_STEP_HPP

namespace Murat {

    class TimeStep {
    public:
        explicit TimeStep(double time = 0.0f)
                : m_Time(time) {
        }

        explicit operator double() const { return m_Time; }

        [[nodiscard]] inline double getSeconds() const { return m_Time; }

        [[nodiscard]] inline double getMilliseconds() const { return m_Time * 1000.0f; }

    private:
        double m_Time;
    };

}

#endif


