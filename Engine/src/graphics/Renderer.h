#pragma once

#include "Window.h"
#include "Log.h"

namespace Planets {
    
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        bool init();
        void render() const;
        void shutdown();

        bool shouldClose() const;

    private:
        Window window;
    };

}
