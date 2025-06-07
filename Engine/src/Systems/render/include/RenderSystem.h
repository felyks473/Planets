#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "System.h"
#include "Shader.h"
#include "SphereComponent.h"
#include "TransformComponent.h"

#include <cstdint>
#include <memory>

namespace Planets
{
    class RenderSystem : public System
    {
    public:
        RenderSystem(const std::uint32_t VAO, std::shared_ptr<Shader> shader, SphereComponent* component, const int windowWidth, const int windowHeight);
        ~RenderSystem() = default;

        void Update();
    private:
        const std::uint32_t VAO;
        std::shared_ptr<Shader> shader;
        SphereComponent* component;
        const int windowWidth;
        const int windowHeight;
        std::unique_ptr<TransformComponent> transformComponent;
    };
}
