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
#include "../ResourceManager.h"

class Renderer {
private:

    Camera camera;

    GLuint vao = 0;
    GLuint ubo_matrix_handle;
    GLuint ubo_light_handle;

    glm::vec3 lightPos;

    ResourceManager* resourceManager;

public:

    void init();

    std::vector<StaticModel> staticModels;

    void draw();

    Renderer();

    ~Renderer();

    void drawStaticModels();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods);

    void updateLightPosition() const;

    void updateMatrices(const StaticModel &model) const;
};


#endif //TESTGLEW_RENDERER_H


