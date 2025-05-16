#include "RenderSystem.h"

namespace Planets {

    RenderSystem::RenderSystem(const std::uint32_t VAO, Shader* shader, SphereComponent* component, const int windowWidth, const int windowHeight) : VAO(VAO), shader(shader), component(component), windowWidth(windowWidth), windowHeight(windowHeight) {}
    
    RenderSystem::~RenderSystem() {}

    void RenderSystem::Update()
    { 

        transformComponent->Update(windowWidth, windowHeight, shader);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, component->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
