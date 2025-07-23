#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace Planets {

    class SphereComponent : public Component
    {
    public:
        SphereComponent(float r = 1.5f);
        ~SphereComponent() = default;

        void update();
        std::uint32_t getVAO() const;
        std::vector<std::uint32_t>& getIndices();
    private:
        std::uint32_t VAO;
        std::vector<std::uint32_t> indices;
    };

}
