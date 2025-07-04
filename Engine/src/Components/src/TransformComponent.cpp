#include "TransformComponent.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Planets {

    void TransformComponent::Update(int windowWidth, int windowHeight, std::shared_ptr<Shader> shader, int shader_flag)
    {
        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 tilt = glm::mat4(1.0f);
    
        if (shader_flag == 0) // Earth
        {
            tilt = glm::rotate(tilt, glm::radians(23.5f), glm::vec3(1.0f, 0.0f, 0.0f));
            
            model = model * tilt;

            view = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -5.0f, -30.0f));
            float angle = 25.0f * static_cast<float>(glfwGetTime());
            float angleDegree = 23.5f;
    
            float angleRadians = glm::radians(angleDegree);

            glm::vec3 axis = glm::normalize(glm::vec3(sin(angleRadians), cos(angleRadians), 0.0f));
            model = glm::rotate(model, glm::radians(angle), axis);
        }
        if (shader_flag == 1) // Sun
        {
            model = glm::translate(model, glm::vec3(10.0f, 10.0f, 0.0f));
            model = glm::scale(model, glm::vec3(2.0f, 2.0f, 1.0f));
            tilt = glm::rotate(tilt, glm::radians(7.25f), glm::vec3(1.0f, 0.0f, 0.0f));
        
            model = model * tilt;

            view = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -5.0f, -30.0f));
        }
        if (shader_flag == 2) // Moon
        {
            model = glm::translate(model, glm::vec3(5.0f, 5.0f, 0.0f));
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
            tilt = glm::rotate(tilt, glm::radians(5.14f), glm::vec3(1.0f, 0.0f, 0.0f));
        
            model = model * tilt;

            view = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -10.0f, -30.0f));
        }
        if (shader_flag == 3)
        {
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));

            view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        }
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model;

        shader->setMat4("mvp", mvp);
    }

}
