#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.h"
#include "World.h"
#include "Shader.h"

#include <memory>
#include <vector>

#include <CameraSystem.h>

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
        void mouse_callback([[maybe_unused]] GLFWwindow* window, double xposIn, double yposIn);
    private:
        GLFWwindow* window;
        World world;
        std::vector<std::shared_ptr<Shader>> shaders;
        
        CameraSystem camera;
        float lastX;
        float lastY;
        float dt;
        float lastFrame;
        bool firstMouse;
        
        bool canMoveKeyboard;
        bool canMoveMouse;
        
        bool mode;
        bool atmosphere;
        bool night;
        std::vector<bool*> stop;
        
        std::vector<float> default_value;
        std::vector<float*> slider_value;
    };

}
