#pragma once

#include "Shader.h"

#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    class TransformComponent 
    {
    public:
        TransformComponent();
        ~TransformComponent() = default;
    
        void Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader, int shader_flag);
    private:
        glm::mat4 view;
        glm::vec3 earthPosition;
        glm::vec3 moonPosition;
        float earthOrbitSpeed;
        float angleDegree;
        float angleRadians;
        float distanceFromEarthX;
        float distanceFromEarthZ;
        float distanceFromMoonX;
        float distanceFromMoonZ;
        float days;
        glm::vec3 earthAxis;
        glm::vec3 sunAxis;
        glm::vec3 moonAxis;
    };

}
