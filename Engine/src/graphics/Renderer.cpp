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

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        return true;
    }

    void Renderer::render() const
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window.update();
        glfwSwapBuffers(window.getWindow());
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
