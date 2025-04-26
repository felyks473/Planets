#pragma once

#include <vector>
#include <memory>
#include "System.h"

namespace Planets {
 
    class SystemManager
    {
    public:
        void Add(std::shared_ptr<Planets::System> sys)
        {
            systems.push_back(sys);
        }

        template <typename T, typename... Args>
        void Create(Args&&... args)
        {
            auto system = std::make_shared<T>(std::forward<Args>(args)...);
            systems.push_back(system);
        }

        void Remove(std::shared_ptr<Planets::System> sys)
        {
            auto it = std::find(systems.begin(), systems.end(), sys);
            if (it != systems.end())
            {
                systems.erase(it);
            }
        }

        void Update()
        {
            for (auto& system : systems)
            {
                system->Update();
            }
        }

    private:
        std::vector<std::shared_ptr<Planets::System>> systems;
    };

}
