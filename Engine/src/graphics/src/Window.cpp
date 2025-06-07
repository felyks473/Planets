#include "Window.h"

#include "Entity.h"
#include "RenderSystem.h"
#include "SphereComponent.h"

#include <filesystem>

namespace Planets {

    Window::Window(int width, int height, const char* title)
    : window(nullptr)
    {
        if (!glfwInit())
        {
            EH_CORE_ERROR("GLFW init failed\n");
        }
    
        EH_CORE_INFO("GLFW initialized successfully\n");

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            EH_CORE_ERROR("Failed to open the window\n")
            glfwTerminate();
        }

        EH_CORE_INFO("Window opened successfully\n");

        glfwMakeContextCurrent(window);
        
        glfwSetFramebufferSizeCallback(window, [] ( [[maybe_unused]] GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        } );
    
        glfwSwapInterval(1); // vsync
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            EH_CORE_ERROR("Failed to init OPGL context\n");
        }
        
        EH_CORE_INFO("OPGL context initialized successfully\n");
        Entity entity = world.CreateEntity();
        SphereComponent* comp = world.AddComponent<SphereComponent>(entity.getID());
        
        std::filesystem::path vfPath = "../Engine/src/shader/sphere_shader.vs";
        std::filesystem::path ffPath = "../Engine/src/shader/sphere_shader.fs";

        std::string vPath = vfPath.string();    
        std::string fPath = ffPath.string();

        shader = std::make_shared<Shader>(vPath.c_str(), fPath.c_str());
        world.CreateSystem<RenderSystem>(comp->getVAO(), shader, comp, width, height);
    }

    Window::~Window()
    {
        shader->cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::update()
    {
        processInput();
        glfwPollEvents();
        world.Update();
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    GLFWwindow* Window::getWindow() const 
    {
        return window;
    }

    void Window::processInput()
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }   

}
