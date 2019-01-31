cmake_minimum_required(VERSION 3.12)
project(TerrenRendering)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(TerrenRenderingTarget
        Source/main.cpp
        Source/Engine/Renderer/Shader.cpp
        Source/Engine/Renderer/Shader.h
        Source/Engine/Renderer/Camera.cpp
        Source/Engine/Renderer/Camera.h
        Source/Engine/Renderer/Renderer.cpp
        Source/Engine/Renderer/Renderer.h
        Source/Engine/EngineApplication.h
        Source/Engine/EngineApplication.cpp
        Source/Engine/ResorceManager.h
        Source/Engine/ResorceManager.cpp
        Source/Engine/Renderer/Technique.h
        Source/Engine/Renderer/Technique.cpp
        )

target_link_libraries(TerrenRenderingTarget ${CONAN_LIBS})

file( COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin )

