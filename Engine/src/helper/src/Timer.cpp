#include "Timer.h"

namespace Planets {

    void Timer::start()
    {
        start_time = glfwGetTime();
        pausedTime = 0.0f;
        running = true;
    }

    void Timer::pause()
    {
        if (running)
        {
            pause_start = glfwGetTime();
            running = false;
        }
    }

    void Timer::resume()
    {
        if(!running)
        {
            pausedTime += glfwGetTime() - pause_start;
            running = true;
        }
    }

    double Timer::getTime()
    {
        if (!running)
        {
            return pause_start - start_time - pausedTime;
        }
        return glfwGetTime() - start_time - pausedTime;
    }

    void Timer::setTime(float time)
    {
        double now = glfwGetTime();
        if (running)
            start_time = now - time;
        else
        {
            pausedTime = 0.0;
            start_time = now - time;
            pause_start = now;
        }
    }
}
