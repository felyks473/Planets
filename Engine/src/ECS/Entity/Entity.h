#pragma once

#include <cstdint>

namespace Planets
{
    class Entity
    {
    public:
        using ID = std::uint32_t;
    
        Entity() : m_id(0) {}
        Entity(ID id) : m_id(id) {}
        ID getID() const { return m_id; }

    private:
        ID m_id;
    };

}
