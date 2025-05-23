#include <EntityManager.h>
#include <ComponentManager.h>
#include <SystemManager.h>

#include <memory>
#include <vector>

namespace Planets {
    
    class World
    {
    public:
        World();
        ~World();
    
        Entity CreateEntity();
        void DestroyEntity(Entity e);
    
        template <typename T, typename... Args>
        void CreateSystem(Args&&... args);
        void AddSystem(std::shared_ptr<System> sys);
        void RemoveSystem(std::shared_ptr<System> sys);
        void Update() const;
        template <typename T>
        T* AddComponent(std::uint32_t ID);
    public:
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;
    };

}

template <typename T, typename... Args>
void Planets::World::CreateSystem(Args&&... args)
{
    systemManager->Create<T>(std::forward<Args>(args)...);
}

template <typename T>
T* Planets::World::AddComponent(std::uint32_t ID)
{
    return componentManager->addComponent<T>(ID);
}
