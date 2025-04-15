#include "Window.h"
#include <iostream>

namespace Planets {

    Window::Window()
    : window(nullptr)
    {
    }

    Window::~Window()
    {
        shutdown();
    }

    bool Window::init(int width, int height, const char* title)
    {
        if (!glfwInit())
        {
            EH_CORE_ERROR("GLFW init failed\n");
            return false;
        }
    
        EH_CORE_INFO("GLFW initialized successfully\n");

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            EH_CORE_ERROR("Failed to open the window\n")
            glfwTerminate();
            return false;
        }

        EH_CORE_INFO("Window opened successfully\n");

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // vsync
        return true;
    }

    void Window::update()
    {
        processInput();
        glfwPollEvents();
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    GLFWwindow* Window::getWindow() const 
    {
        return window;
    }

    void Window::shutdown()
    {
        if (window)
        {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }

    void Window::processInput()
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }   

}
