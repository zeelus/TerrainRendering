cmake_minimum_required(VERSION 3.12)
project(TerrenRendering)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(TerrenRenderingTarget Source/main.cpp Source/Renderer/Shader.cpp Source/Renderer/Shader.h Source/Renderer/Camera.cpp Source/Renderer/Camera.h Source/Renderer/Renderer.cpp Source/Renderer/Renderer.h)

target_link_libraries(TerrenRenderingTarget ${CONAN_LIBS})

file( COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin )

