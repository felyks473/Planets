#include <EntityManager.h>
#include <ComponentManager.h>
#include <SystemManager.h>

#include <memory>
#include <vector>

#include <CameraSystem.h>

namespace Planets {
    
    class World
    {
    public:
        World();
        ~World() = default;
    
        Entity CreateEntity();
        void DestroyEntity(Entity e);
    
        template <typename T, typename... Args>
        void CreateSystem(Args&&... args);
        void AddSystem(std::shared_ptr<System> sys);
        void RemoveSystem(std::shared_ptr<System> sys);
        void Update(std::vector<std::shared_ptr<Shader>> shader, CameraSystem camera, std::vector<bool*>& stop, std::vector<float*>& slider_value) const;
        template <typename T>
        T* AddComponent(std::uint32_t ID);
    public:
        std::shared_ptr<EntityManager> entityManager;
        std::shared_ptr<ComponentManager> componentManager;
        std::shared_ptr<SystemManager> systemManager;
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
