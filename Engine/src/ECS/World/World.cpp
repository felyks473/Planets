#include "World.h"

namespace Planets {
    
    World::World()
    : entityManager(std::make_unique<EntityManager>()), componentManager(std::make_unique<ComponentManager>()), systemManager(std::make_unique<SystemManager>())
    {
    }

    World::~World() {}

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
