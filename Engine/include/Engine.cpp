#include "Engine.h"

namespace Planets {

    Engine::Engine()
    : isRunning(false), renderer(std::make_shared<Renderer>()) {}

    Engine::~Engine()
    {
        EH_CORE_INFO("Turning off the engine\n");
        shutdown();
    }

    bool Engine::init() const
    {
        Log::Init();

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

    void Engine::shutdown() const
    {
        renderer->shutdown();
    }

    void Engine::gameLoop() const
    {
        while (isRunning && !renderer->shouldClose())
        {
            renderer->render();
        }
    }

}
