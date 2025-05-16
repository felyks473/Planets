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

        bool init() const;
        void run();
        void shutdown() const;

    private:
        void gameLoop() const;

        bool isRunning;
        std::shared_ptr<Renderer> renderer;
    };

}
