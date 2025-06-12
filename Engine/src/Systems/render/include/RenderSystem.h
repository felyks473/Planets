#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "System.h"
#include "Shader.h"
#include "SphereComponent.h"
#include "TransformComponent.h"

#include <cstdint>
#include <memory>
#include <vector>

#include "Texture.h"

namespace Planets
{
    class RenderSystem : public System
    {
    public:
        RenderSystem(std::vector<std::uint32_t> VAOS, std::vector<SphereComponent*> components, const int windowWidth, const int windowHeight);
        ~RenderSystem() = default;

        void Update(std::vector<std::shared_ptr<Shader>> shaders);
    private:
        const std::uint32_t VAO_EARTH;
        const std::uint32_t VAO_SUN;
        const std::uint32_t VAO_MOON;
    
        std::vector<SphereComponent*> components;
        const int windowWidth;
        const int windowHeight;
        std::unique_ptr<TransformComponent> EarthTransformComponent;
        std::unique_ptr<TransformComponent> SunTransformComponent;
        std::unique_ptr<TransformComponent> MoonTransformComponent;
        Texture earthTexture;
        Texture sunTexture;
        Texture moonTexture;
    };
}
