#include <CameraSystem.h>

namespace Planets {

CameraSystem::CameraSystem(glm::vec3 position, glm::vec3 up) : Position(position), Front(glm::vec3(0.0f, 0.0f, 49.0f)), Up(up), WorldUp(up), YAW(-90.0f), PITCH(0.0f), MovementSpeed(10.0f), MouseSensitivity(0.15f)
    {
        updateCameraVectors();
    }

    glm::vec3 CameraSystem::getPosition() const
    {
        return Position;
    }

    glm::mat4 CameraSystem::GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    void CameraSystem::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        YAW   += xoffset;
        PITCH += yoffset;

        if (constrainPitch)
        {
            if (PITCH > 89.0f)
                PITCH = 89.0f;
            if (PITCH < -89.0f)
                PITCH = -89.0f;
        }

        updateCameraVectors();
    }

    void CameraSystem::ProcessKeyboard(Camera_Movement direction, float dt)
    {
        float velocity = MovementSpeed * dt;
        if (direction == FORWARD)
            Position += Front * velocity;
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
            Position += Right * velocity;
    }

    void CameraSystem::updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
        front.y = sin(glm::radians(PITCH));
        front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
        Front = glm::normalize(front);
        
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up    = glm::normalize(glm::cross(Right, Front));
    }
}
