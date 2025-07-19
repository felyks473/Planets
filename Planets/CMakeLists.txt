file(GLOB IMGUI_SRC
    "${CMAKE_SOURCE_DIR}/lib/imgui/*.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp"
)

add_executable(Planets src/main.cpp src/Game.cpp ${IMGUI_SRC})

target_include_directories(Planets PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Engine/include>
)

if(UNIX)
    target_link_libraries(Planets PRIVATE Engine OpenGL::GL glfw)
elseif(WIN32)
    target_link_libraries(Planets PRIVATE Engine opengl32 glfw)
endif()
