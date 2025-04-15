#pragma once

#include <memory>
#include "Renderer.h"

#include "Log.h"

namespace Planets {
    
    class Engine
    {
    public:
        Engine();
        ~Engine();

        bool init();
        void run();
        void shutdown();

    private:
        void gameLoop();

        bool isRunning;
        std::shared_ptr<Planets::Renderer> renderer;
    };

}
