#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "World.h"

namespace Planets {
    
    class Window
    {
    public:
        Window();
        ~Window();

        bool init(int width, int height, const char* title);
        void update() const;
        bool shouldClose() const;
        GLFWwindow* getWindow() const;
        void shutdown();
        void processInput() const;
    private:
        GLFWwindow* window;
        World world;
    };

}
