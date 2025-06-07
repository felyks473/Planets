#pragma once

#include "Window.h"
#include "Log.h"

namespace Planets {
    
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() = default;

        void render();
        bool shouldClose() const;

    private:
        Window window;
    };

}
