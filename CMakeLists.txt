cmake_minimum_required(VERSION 3.13)
project(TerrenRendering)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(OpenGL REQUIRED)

add_executable(TerrenRenderingTarget Source/main.cpp Source/Renderer/Shader.cpp Source/Renderer/Shader.h Source/Renderer/Camera.cpp Source/Renderer/Camera.h Source/Renderer/Renderer.cpp Source/Renderer/Renderer.h)

target_link_libraries(TerrenRenderingTarget ${CONAN_LIBS} ${OPENGL_gl_LIBRARY})

file( COPY Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin )