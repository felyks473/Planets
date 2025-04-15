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
        void DestroyEntity(Planets::Entity e);
    
        template <typename T, typename... Args>
        void CreateSystem(Args&&... args);
        void AddSystem(std::shared_ptr<Planets::System> sys);
        void RemoveSystem(std::shared_ptr<Planets::System> sys);
        void Update(float dt);
    public:
        std::unique_ptr<Planets::EntityManager> entityManager;
        std::unique_ptr<Planets::ComponentManager> componentManager;
        std::unique_ptr<Planets::SystemManager> systemManager;
    };

}
