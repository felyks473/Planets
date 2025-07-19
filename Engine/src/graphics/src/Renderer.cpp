#include <glad/glad.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Renderer.h"

namespace Planets {
    
    Renderer::Renderer()
    : window(800, 600, "Planets")
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        ImGui::StyleColorsDark();
    }

    void Renderer::render()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.update();
        glfwSwapBuffers(window.getWindow());
    }

    bool Renderer::shouldClose() const
    {
        return window.shouldClose();
    }

}
