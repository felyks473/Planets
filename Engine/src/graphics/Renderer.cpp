#include <glad/glad.h>
#include "Renderer.h"
#include <iostream>

namespace Planets {
    
    Renderer::Renderer() {}
    Renderer::~Renderer() { shutdown(); }

    bool Renderer::init()
    {
        if (!window.init(800, 600, "Planets"))
        {
            EH_CORE_ERROR("Failed to init window\n");
            return false;
        }

        EH_CORE_INFO("Window initialized successfully\n");
    
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            EH_CORE_ERROR("Failed to init OPGL context\n");
            return false;
        }
        
        EH_CORE_INFO("OPGL context initialized successfully\n");

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        return true;
    }

    void Renderer::render()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.getWindow());
        window.update();
    }

    void Renderer::shutdown()
    {
        window.shutdown();
    }

    bool Renderer::shouldClose() const
    {
        return window.shouldClose();
    }

}
