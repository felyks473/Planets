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
        
        Entity earth = world.CreateEntity();
        Entity sun = world.CreateEntity();
        Entity moon = world.CreateEntity();
        Entity stars = world.CreateEntity();

        SphereComponent* earth_comp = world.AddComponent<SphereComponent>(earth.getID());
        SphereComponent* sun_comp = world.AddComponent<SphereComponent>(sun.getID());
        SphereComponent* moon_comp = world.AddComponent<SphereComponent>(moon.getID());
        SphereComponent* stars_comp = world.AddComponent<SphereComponent>(stars.getID());
        
        std::filesystem::path vfPath = "../Engine/src/shader/sphere_shader.vs";
        std::filesystem::path ffPath = "../Engine/src/shader/sphere_shader.fs";

        std::string vPath = vfPath.string();    
        std::string fPath = ffPath.string();

        shaders.push_back(std::make_shared<Shader>(vPath.c_str(), fPath.c_str()));
        
        vfPath = "../Engine/src/shader/sun_shader.vs";
        ffPath = "../Engine/src/shader/sun_shader.fs";

        vPath = vfPath.string();
        fPath = ffPath.string();

        shaders.push_back(std::make_shared<Shader>(vPath.c_str(), fPath.c_str()));

        vfPath = "../Engine/src/shader/moon_shader.vs";
        ffPath = "../Engine/src/shader/moon_shader.fs";

        vPath = vfPath.string();
        fPath = ffPath.string();

        shaders.push_back(std::make_shared<Shader>(vPath.c_str(), fPath.c_str()));

        vfPath = "../Engine/src/shader/stars_shader.vs";
        ffPath = "../Engine/src/shader/stars_shader.fs";

        vPath = vfPath.string();
        fPath = ffPath.string();

        shaders.push_back(std::make_shared<Shader>(vPath.c_str(), fPath.c_str()));
        
        std::vector<SphereComponent*> comps = {earth_comp, sun_comp, moon_comp, stars_comp};
        std::vector<std::uint32_t> vaos = {earth_comp->getVAO(), sun_comp->getVAO(), moon_comp->getVAO(), stars_comp->getVAO()};
        
        world.CreateSystem<RenderSystem>(vaos, comps, width, height);
    }

    Window::~Window()
    {
        for (auto shader : shaders)
            shader->cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::update()
    {
        processInput();
        glfwPollEvents();
        world.Update(shaders);
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
