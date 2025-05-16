#pragma once

#include "Shader.h"

namespace Planets {

    class TransformComponent 
    {
    public:
        TransformComponent();
        ~TransformComponent();
    
        void Update(int windowWidth, int windowHeight, Shader* shader) const;
    };

}
