#include "RenderSystem.h"

namespace Planets {

    RenderSystem::RenderSystem(std::vector<std::uint32_t> VAOS, std::vector<SphereComponent*> components, const int windowWidth, const int windowHeight) : VAO_EARTH(VAOS[0]), VAO_SUN(VAOS[1]), VAO_MOON(VAOS[2]), components(components), windowWidth(windowWidth), windowHeight(windowHeight), earthTexture("../Engine/src/assets/8k_earth_daymap.jpg"), sunTexture("../Engine/src/assets/8k_sun.jpg"), moonTexture("../Engine/src/assets/8k_moon.jpg")
    {
        EarthTransformComponent = std::make_unique<TransformComponent>();
        SunTransformComponent = std::make_unique<TransformComponent>();
        MoonTransformComponent = std::make_unique<TransformComponent>();
    }

    void RenderSystem::Update(std::vector<std::shared_ptr<Shader>> shaders)
    {
        EarthTransformComponent->Update(windowWidth, windowHeight, shaders[0], 0);
        
        earthTexture.bindTexture();
        glBindVertexArray(VAO_EARTH);
        glDrawElements(GL_TRIANGLES, components[0]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);    

        SunTransformComponent->Update(windowWidth, windowHeight, shaders[1], 1);
        
        sunTexture.bindTexture();
        glBindVertexArray(VAO_SUN);
        glDrawElements(GL_TRIANGLES, components[1]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        MoonTransformComponent->Update(windowWidth, windowHeight, shaders[2], 2);
        
        moonTexture.bindTexture();
        glBindVertexArray(VAO_MOON);
        glDrawElements(GL_TRIANGLES, components[2]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
