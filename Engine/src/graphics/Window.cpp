#include "Window.h"

#include "Entity.h"
#include "RenderSystem.h"
#include "SphereComponent.h"
#include "Shader.h"

#include <filesystem>

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
        
        glfwSetFramebufferSizeCallback(window, [] ( [[maybe_unused]] GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        } );
    
        glfwSwapInterval(1); // vsync
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            EH_CORE_ERROR("Failed to init OPGL context\n");
            return false;
        }
        
        EH_CORE_INFO("OPGL context initialized successfully\n");
        Entity entity = world.CreateEntity();
        SphereComponent* comp = world.AddComponent<SphereComponent>(entity.getID());
        Shader* shader = new Shader();
        
        std::filesystem::path vfPath = "../Engine/src/shader/sphere_shader.vs";
        std::filesystem::path ffPath = "../Engine/src/shader/sphere_shader.fs";

        std::string vPath = vfPath.string();    
        std::string fPath = ffPath.string();

        shader->Init(vPath.c_str(), fPath.c_str());
        world.CreateSystem<RenderSystem>(comp->getVAO(), shader, comp, width, height);
        
        return true;
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
