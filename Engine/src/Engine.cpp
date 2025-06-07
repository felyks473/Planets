#include "Engine.h"

namespace Planets {

    Engine::Engine()
    {
        Log::Init();
        renderer = std::make_shared<Renderer>();
        EH_CORE_INFO("Turning on the engine\n");
        
        while (!renderer->shouldClose())
        {
            renderer->render();
        }
    }

    Engine::~Engine()
    {
        EH_CORE_INFO("Turning off the engine\n");
    }

}
