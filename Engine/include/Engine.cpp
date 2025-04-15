#include "Engine.h"
#include <iostream>

namespace Planets {

    Engine::Engine()
    : isRunning(false), renderer(std::make_shared<Planets::Renderer>()) {}

    Engine::~Engine()
    {
        EH_CORE_INFO("Turning off the engine\n");
        shutdown();
    }

    bool Engine::init()
    {
        Planets::Log::Init();

        EH_CORE_INFO("Turning on the engine\n");
        
        if (!renderer->init())
        {
            EH_CORE_ERROR("Renderer could not be initialized\n");
            return false;
        }
        EH_CORE_INFO("Renderer initialized successfully\n");
        return true;
    }

    void Engine::run()
    {
        isRunning = true;
        gameLoop();
    }

    void Engine::shutdown()
    {
        renderer->shutdown();
    }

    void Engine::gameLoop()
    {
        while (isRunning && !renderer->shouldClose())
        {
            renderer->render();
        }
    }

}
