#include "World.h"

namespace Planets {
    
    World::World()
    : entityManager(std::make_unique<Planets::EntityManager>()), componentManager(std::make_unique<Planets::ComponentManager>()), systemManager(std::make_unique<Planets::SystemManager>())
    {
    }

    World::~World() {}

    Entity World::CreateEntity()
    {
        return entityManager->createEntity();
    }

    void World::DestroyEntity(Planets::Entity e)
    {
        entityManager->destroyEntity(e.getID());
    }

    void World::AddSystem(std::shared_ptr<Planets::System> sys)
    {
        systemManager->Add(sys);
    }

    void World::RemoveSystem(std::shared_ptr<Planets::System> sys)
    {
        systemManager->Remove(sys);
    }

    void World::Update()
    {
        systemManager->Update();
    }

}
