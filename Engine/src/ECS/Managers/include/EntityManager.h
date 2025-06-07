#pragma once

#include "Entity.h"
#include <unordered_map>

namespace Planets {

    class EntityManager
    {
    public:
        EntityManager();
        Entity createEntity();
        void destroyEntity(Entity::ID entityID);
        const Entity& getEntity(Entity::ID entityID) const;
    private:
        std::unordered_map<Entity::ID, Entity> m_entities;
        Entity::ID m_nextEntityID;
    };
}
