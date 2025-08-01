#include "RenderSystem.h"

namespace Planets {

    RenderSystem::RenderSystem(std::vector<std::uint32_t> VAOS, std::vector<SphereComponent*> components, const int windowWidth, const int windowHeight) : VAO_EARTH(VAOS[0]), VAO_SUN(VAOS[1]), VAO_MOON(VAOS[2]), VAO_STARS(VAOS[3]), components(components), windowWidth(windowWidth), windowHeight(windowHeight), earthTexture("../Engine/src/assets/8k_earth_daymap.jpg", "../Engine/src/assets/8k_earth_nightmap.jpg", "../Engine/src/assets/8k_earth_clouds.jpg"), sunTexture("../Engine/src/assets/8k_sun.jpg"), moonTexture("../Engine/src/assets/8k_moon.jpg"), starsTexture("../Engine/src/assets/8k_stars_milky_way.jpg")
    {
        EarthTransformComponent = std::make_unique<TransformComponent>();
        SunTransformComponent = std::make_unique<TransformComponent>();
        MoonTransformComponent = std::make_unique<TransformComponent>();
        StarTransformComponent = std::make_unique<TransformComponent>();
    }

    void RenderSystem::Update(std::vector<std::shared_ptr<Shader>> shaders, CameraSystem &camera, std::vector<bool*>& stop, std::vector<float*>& slider_value)
    {
        EarthTransformComponent->Update(windowWidth, windowHeight, shaders[0], 0, camera, stop, slider_value);
        shaders[0]->setInt("Texture0", 0);
    
        glBindVertexArray(VAO_EARTH);
        glActiveTexture(GL_TEXTURE0);

        earthTexture.bindTexture(earthTexture.getID()[0]);
        shaders[0]->setInt("Texture1", 1);
        
        glActiveTexture(GL_TEXTURE1);
        earthTexture.bindTexture(earthTexture.getID()[1]);
        
        if (*stop[1])
        {
            shaders[0]->setInt("Texture2", 2);
            glActiveTexture(GL_TEXTURE2);
            earthTexture.bindTexture(earthTexture.getID()[2]);
            shaders[0]->setInt("state", 1);
        }
        glDrawElements(GL_TRIANGLES, components[0]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        earthTexture.bindTexture(0);
        SunTransformComponent->Update(windowWidth, windowHeight, shaders[1], 1, camera, stop, slider_value);
        
        glActiveTexture(GL_TEXTURE0);
        sunTexture.bindTexture(sunTexture.getID()[0]);
        glBindVertexArray(VAO_SUN);
        glDrawElements(GL_TRIANGLES, components[1]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        MoonTransformComponent->Update(windowWidth, windowHeight, shaders[2], 2, camera, stop, slider_value);
        
        moonTexture.bindTexture(moonTexture.getID()[0]);
        glBindVertexArray(VAO_MOON);
        glDrawElements(GL_TRIANGLES, components[2]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        StarTransformComponent->Update(windowWidth, windowHeight, shaders[3], 3, camera, stop, slider_value);
        
        starsTexture.bindTexture(starsTexture.getID()[0]);
        glBindVertexArray(VAO_STARS);
        glDrawElements(GL_TRIANGLES, components[3]->getIndices().size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}
