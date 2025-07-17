set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/src/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/src/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Entity/src/EntityManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/World/src/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper/src/Log.cpp
    ${CMAKE_SOURCE_DIR}/lib/glad.c
    ${CMAKE_SOURCE_DIR}/lib/additional.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/src/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Systems/render/src/RenderSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Systems/camera/src/CameraSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/src/SphereComponent.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/src/TransformComponent.cpp
)

add_library(Engine ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Managers/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Entity/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/World/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Systems/render/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Systems/camera/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/include
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/spdlog/include
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/glfw/include
)
