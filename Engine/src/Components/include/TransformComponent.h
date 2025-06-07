#pragma once

#include "Shader.h"

#include <memory>

namespace Planets {

    class TransformComponent 
    {
    public:
        TransformComponent() = default;
        ~TransformComponent() = default;
    
        void Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader);
    };

}
