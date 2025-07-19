#pragma once

#include "Shader.h"
#include <memory>
#include <vector>
#include <CameraSystem.h>

namespace Planets {
 
    class System
    {
    public:
        virtual ~System() = default;

        virtual void Update(std::vector<std::shared_ptr<Shader>> shader, CameraSystem& camera, std::vector<bool*>& stop, std::vector<float*>& slider_value) = 0;
    };

}
