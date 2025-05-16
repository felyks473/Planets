#pragma once

#include <unordered_map>
#include <vector>
#include <memory>
#include "Component.h"

namespace Planets {

    class ComponentManager
    {
    public:
        template <typename T, typename... Args>
        T* addComponent(int entityID, Args&&... args)
        {
            auto component = std::make_unique<T>(std::forward<Args>(args)...);
            T* componentPtr = component.get();
            components[entityID].emplace_back(std::move(component));
            return componentPtr;
        }

        void updateComponents() const
        {
            for (auto& pair : components)
            {
                for (auto& component : pair.second)
                {
                    component->update();
                }
            }
        }

    private:
        std::unordered_map<int, std::vector<std::unique_ptr<Component>>> components;
    };

}
