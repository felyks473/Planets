#include "Window.h"

#include "Entity.h"
#include "RenderSystem.h"
#include "SphereComponent.h"

#include <filesystem>
#include <glm/glm.hpp>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Planets {

    Window::Window(int width, int height, const char* title)
    : window(nullptr), camera(glm::vec3(0.0f, 0.0f, 50.0f)), lastX(static_cast<float>(width) / 2.0f), lastY(static_cast<float>(height / 2.0f)), firstMouse(true), canMoveKeyboard(false), canMoveMouse(false), mode(false), default_value{0.0f, 0.0f, 14.9f, 3.48f}
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
    
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) {
            auto app = static_cast<Window*>(glfwGetWindowUserPointer(w));
            app->mouse_callback(w, x, y);
        });
    
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

        stop.push_back(&mode);
        
        for (auto &value : default_value)
        {
            slider_value.push_back(&value);
        }      
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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        float currentFrame = static_cast<float>(glfwGetTime());
        dt = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput();
        glfwPollEvents();
        
        world.Update(shaders, camera, stop, slider_value);
        
        ImGui::Begin("Debug");
        if (ImGui::Button("Reset camera"))
            camera.resetCamera();

        const char* messageKeyboard = (canMoveKeyboard ? "Lock movement" : "Unlock movement");
        const char* messageMouse = (canMoveMouse ? "Lock mouse" : "Unlock mouse");
        ImGui::Checkbox(messageKeyboard, &canMoveKeyboard);
        ImGui::SameLine();
        ImGui::Checkbox(messageMouse, &canMoveMouse);
        
        const char* messageTime = (*stop[0] ? "Manual" : "Automatic");
        ImGui::Checkbox(messageTime, stop[0]);
        ImGui::SliderFloat("Earth orbit", slider_value[0], 0.0f, 5.51f);
        ImGui::SliderFloat("Moon orbit", slider_value[1], 0.0f, 4.12f);
        ImGui::SliderFloat("Earth distance (from Sun)", slider_value[2], 0.0f, 100.0f);
        ImGui::SliderFloat("Moon distance (from Earth)", slider_value[3], 0.0f, 100.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        
        if (canMoveKeyboard)
        {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                camera.ProcessKeyboard(FORWARD, dt);
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                camera.ProcessKeyboard(BACKWARD, dt);
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                camera.ProcessKeyboard(LEFT, dt);
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                camera.ProcessKeyboard(RIGHT, dt);
        }
    }   

    void Window::mouse_callback([[maybe_unused]] GLFWwindow* window, double xposIn, double yposIn)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        if (canMoveMouse)
            camera.ProcessMouseMovement(xoffset, yoffset);
    }

}
