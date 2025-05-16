#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "System.h"
#include "Shader.h"
#include "SphereComponent.h"
#include "TransformComponent.h"

#include <cstdint>

namespace Planets
{
    class RenderSystem : public System
    {
    public:
        RenderSystem(const std::uint32_t VAO, Shader* shader, SphereComponent* component, const int windowWidth, const int windowHeight);
        ~RenderSystem();

        void Update();
    private:
        const std::uint32_t VAO;
        Shader* shader;
        SphereComponent* component;
        const int windowWidth, windowHeight;
        TransformComponent* transformComponent;
    };
}
