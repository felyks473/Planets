#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Planets {
    
    class Timer
    {
    public:
        Timer() = default;
        ~Timer() = default;
        void start();
        void pause();
        void resume();
        double getTime();
        void setTime(float time);
    private:
        double start_time;
        double pausedTime;
        bool running;
        double pause_start;
    };
}
