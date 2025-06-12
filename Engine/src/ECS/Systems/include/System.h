#pragma once

#include "Shader.h"
#include <memory>
#include <vector>

namespace Planets {
 
    class System
    {
    public:
        virtual ~System() = default;

        virtual void Update(std::vector<std::shared_ptr<Shader>> shader) = 0;
    };

}
