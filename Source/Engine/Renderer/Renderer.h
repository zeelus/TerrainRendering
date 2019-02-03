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

    void updateCamera(GLuint shader_programme);

    Technique *technique;

public:

    void init();

    std::vector<StaticModel> models;

    void drowing();

    Renderer();

    ~Renderer();

};


#endif //TESTGLEW_RENDERER_H


