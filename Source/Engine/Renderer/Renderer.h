//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#include "Camera.h"
#include "Technique.h"
#include "Shader.h"
#include "StaticModel.h"

class Renderer {
private:

    Camera camera;


    Technique *technique;

    GLuint vao = 0;
    GLuint ubo_matrix_handle;
    GLuint ubo_light_handle;

    const GLuint vertex_position_loction = 0u;
    const GLuint vertex_normal_loction = 1u;

    const GLuint matricesBlockBinding = 0u;
    const GLuint pointLight = 1u;

public:

    void init();

    std::vector<StaticModel> staticModels;

    void draw();

    Renderer();

    ~Renderer();

    void drawStaticModels();
};


#endif //TESTGLEW_RENDERER_H


