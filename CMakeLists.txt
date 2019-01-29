cmake_minimum_required(VERSION 3.12)
project(TerrenRendering)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(TerrenRenderingTarget
        Source/main.cpp
        Source/Engine/Renderer/Shader.cpp
        Source/Engine/Renderer/Shader.h
        Source/Engine/Component/CameraComponent.cpp
        Source/Engine/Component/CameraComponent.h
        Source/Engine/Renderer/RendererSystem.cpp
        Source/Engine/Renderer/RendererSystem.h
        Source/Engine/EngineApplication.h
        Source/Engine/EngineApplication.cpp
        Source/Engine/AbstractScene.h
        Source/Engine/AbstractScene.cpp
        Source/Scene.h
        Source/Scene.cpp
        Source/Engine/GameElement.h
        Source/Engine/GameElement.cpp
        Source/Engine/Component/Component.h
        Source/Engine/Component/Component.cpp
        )

target_link_libraries(TerrenRenderingTarget ${CONAN_LIBS})

file( COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin )

