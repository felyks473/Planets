#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "World.h"
#include "Shader.h"

#include <memory>

namespace Planets {
    
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void update();
        bool shouldClose() const;
        GLFWwindow* getWindow() const;
        void processInput();
    private:
        GLFWwindow* window;
        World world;
        std::shared_ptr<Shader> shader;
    };

}
