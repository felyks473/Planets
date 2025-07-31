#pragma once

#include "Shader.h"

#include <memory>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <CameraSystem.h>

#include <Timer.h>

namespace Planets {

    class TransformComponent 
    {
    public:
        TransformComponent();
        ~TransformComponent() = default;
    
        void Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader, int shader_flag, CameraSystem &camera, std::vector<bool*>& stop, std::vector<float*>& slider_value);
    private:
        glm::mat4 view;
        glm::vec3 earthPosition;
        glm::vec3 moonPosition;
        float earthOrbitSpeed;
        float angleDegree;
        float angleRadians;
        float distanceFromEarthX;
        float distanceFromEarthZ;
        float distanceFromMoon;
        float days;
        glm::vec3 earthAxis;
        glm::vec3 sunAxis;
        glm::vec3 moonAxis;
        Timer earth_timer;
        Timer moon_timer;
        Timer sun_timer;
    };

}
