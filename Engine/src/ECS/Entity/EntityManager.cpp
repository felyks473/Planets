#include "EntityManager.h"

namespace Planets {

    EntityManager::EntityManager() : m_nextEntityID(0) {}

    Entity EntityManager::createEntity()
    {
        Entity::ID newID = m_nextEntityID++;
        Entity newEntity(newID);
        m_entities[newID] = newEntity;
        return newEntity;
    }

    void EntityManager::destroyEntity(Entity::ID entityID)
    {
        auto it = m_entities.find(entityID);
        if (it != m_entities.end())
        {
            m_entities.erase(it);
        }
    }

    Entity EntityManager::getEntity(Entity::ID entityID) const
    {
        return m_entities.at(entityID);
    }

}
