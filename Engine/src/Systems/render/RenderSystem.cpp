#include "RenderSystem.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Planets {

    RenderSystem::RenderSystem(std::uint32_t VAO, Shader* shader, SphereComponent* component, int windowWidth, int windowHeight) : VAO(VAO), shader(shader), component(component), windowWidth(windowWidth), windowHeight(windowHeight) {}
    
    RenderSystem::~RenderSystem() {}

    void RenderSystem::Update() { 

        shader->Use();

        glm::mat4 model = glm::mat4(1.0f);

        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        float angle = 25 * (float)glfwGetTime();
        view = glm::rotate(view, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model;

        shader->setMat4("mvp", mvp);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // So that we can see the sphere rotating a little bit better

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, component->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
