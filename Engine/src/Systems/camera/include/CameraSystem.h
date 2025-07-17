#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Planets {
    
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class CameraSystem
    {
    public:
        CameraSystem(glm::vec3 position = glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3 up = glm::vec3(0.0f, 51.0f, 0.0f));
        ~CameraSystem() = default;
        glm::vec3 getPosition() const;
        glm::mat4 GetViewMatrix();
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
        void ProcessKeyboard(Camera_Movement direction, float dt);
    private:
        void updateCameraVectors();
    private:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;
    
        float YAW;
        float PITCH;
    
        float MovementSpeed;
        float MouseSensitivity;
    };

}
