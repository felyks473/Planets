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
    private:
        std::shared_ptr<Renderer> renderer;
    };

}
