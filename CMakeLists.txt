cmake_minimum_required(VERSION 3.22.1)
project(Earth LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_subdirectory(Engine)
add_subdirectory(Planets)

if(CMAKE_CONFIGURATION_TYPES)
    if(CMAKE_CFG_INTDIR MATCHES "Debug|Testing")
        add_subdirectory(Testing)
    endif()
else()
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Testing")
        add_subdirectory(Testing)
    endif()
endif()
