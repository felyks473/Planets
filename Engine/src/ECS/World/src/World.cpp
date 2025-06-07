#include "World.h"

namespace Planets {
    
    World::World()
    : entityManager(std::make_shared<EntityManager>()), componentManager(std::make_shared<ComponentManager>()), systemManager(std::make_shared<SystemManager>())
    {
    }

    Entity World::CreateEntity()
    {
        return entityManager->createEntity();
    }

    void World::DestroyEntity(Entity e)
    {
        entityManager->destroyEntity(e.getID());
    }

    void World::AddSystem(std::shared_ptr<System> sys)
    {
        systemManager->Add(sys);
    }

    void World::RemoveSystem(std::shared_ptr<System> sys)
    {
        systemManager->Remove(sys);
    }

    void World::Update() const
    {
        systemManager->Update();
    }

}
