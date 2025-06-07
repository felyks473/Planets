#include "TransformComponent.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    void TransformComponent::Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader)
    {
        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 tilt = glm::mat4(1.0f);

        tilt = glm::rotate(tilt, glm::radians(23.5f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = model * tilt;

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        float angle = 25.0f * static_cast<float>(glfwGetTime());

        float angleDegree = 23.5f;
    
        float angleRadians = glm::radians(angleDegree);
        
        glm::vec3 axis = glm::normalize(glm::vec3(sin(angleRadians), cos(angleRadians), 0.0f));
        view = glm::rotate(view, glm::radians(angle), axis);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model;

        shader->setMat4("mvp", mvp);
    }

}
