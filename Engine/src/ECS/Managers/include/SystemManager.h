#pragma once

#include <vector>
#include <memory>
#include "System.h"
#include "Shader.h"
#include <CameraSystem.h>

namespace Planets {
 
    class SystemManager
    {
    public:
        void Add(std::shared_ptr<System> sys)
        {
            systems.push_back(sys);
        }

        template <typename T, typename... Args>
        void Create(Args&&... args)
        {
            auto system = std::make_shared<T>(std::forward<Args>(args)...);
            systems.push_back(system);
        }

        void Remove(std::shared_ptr<System> sys)
        {
            auto it = std::find(systems.begin(), systems.end(), sys);
            if (it != systems.end())
            {
                systems.erase(it);
            }
        }

        void Update(std::vector<std::shared_ptr<Shader>> shaders, CameraSystem camera, std::vector<bool*>& stop, std::vector<float*>& slider_value) const
        {
            for (auto& system : systems)
            {
                system->Update(shaders, camera, stop, slider_value);
            }
        }

    private:
        std::vector<std::shared_ptr<System>> systems;
    };

}
