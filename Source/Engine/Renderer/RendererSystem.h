//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include "../Camera.h"

class RendererSystem {
private:

    //Camera camera;
    entt::registry<>* registryEntt;

    void updateCamera(GLuint shader_programme);
    
public:
    void drowing();

    RendererSystem(entt::registry<>* registryEntt);
};


#endif //TESTGLEW_RENDERER_H
