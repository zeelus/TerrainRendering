cmake_minimum_required(VERSION 3.12)
project(TerrenRenderingEngine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(glbinding REQUIRED)
include_directories(${glbinding_INCLUDE_DIRS})
set(${PROJECT_NAME}_LIBS ${${PROJECT_NAME}_LIBS} ${glbinding_LIBRARIES})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

add_library(TerrenRenderingEngine
        Renderer/Shader.cpp
        Renderer/Shader.h
        Renderer/Camera.cpp
        Renderer/Camera.h
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        EngineApplication.h
        EngineApplication.cpp
        ResourceManager.h
        ResourceManager.cpp
        Renderer/Technique.h
        Renderer/Technique.cpp
        Renderer/Geometry.h
        Renderer/Geometry.cpp
        Renderer/StaticModel.h
        Renderer/StaticModel.cpp
        Renderer/RenderingQueue.cpp Renderer/RenderingQueue.h Renderer/Terrain/TerrainTreeManager.cpp Renderer/Terrain/TerrainTreeManager.h Renderer/Terrain/TerrainTreeNode.cpp Renderer/Terrain/TerrainTreeNode.h)

