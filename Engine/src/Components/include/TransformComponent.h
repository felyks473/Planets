#pragma once

#include "Shader.h"

#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    class TransformComponent 
    {
    public:
        TransformComponent() = default;
        ~TransformComponent() = default;
    
        void Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader, int shader_flag);
    private:
        glm::mat4 view;
    };

}
