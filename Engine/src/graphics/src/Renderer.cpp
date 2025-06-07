#include <glad/glad.h>
#include "Renderer.h"

namespace Planets {
    
    Renderer::Renderer()
    : window(800, 600, "Planets")
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
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
