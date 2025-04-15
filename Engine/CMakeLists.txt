set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Entity/EntityManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/World/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper/Log.cpp
    ${CMAKE_SOURCE_DIR}/lib/glad.c
)

add_library(Engine ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Managers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Entity
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Systems
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/helper
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/spdlog/include
)
