#pragma once

#include "Component.h"

#include <glm/glm.hpp>

namespace Planets {

    class SphereComponent : public Component
    {
    public:
        SphereComponent();
        ~SphereComponent();

        void update();
        std::uint32_t getVAO() const;
        std::vector<std::uint32_t>& getIndices();
    private:
        std::uint32_t VAO;
        std::vector<std::uint32_t> indices;
    };

}
