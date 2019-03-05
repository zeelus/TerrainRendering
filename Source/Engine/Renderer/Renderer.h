//
// Created by Gilbert Gwizdala on 2018-12-25.
//

#ifndef TESTGLEW_RENDERER_H
#define TESTGLEW_RENDERER_H

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <string>
#include <glbinding/gl/gl.h>
#include "Camera.h"
#include "Technique.h"
#include "Shader.h"
#include "StaticModel.h"
#include "../ResourceManager.h"

using namespace gl;

class Renderer {
private:

    Camera camera;

    GLuint vao = 0;
    GLuint ubo_matrix_handle;
    GLuint ubo_light_handle;

    glm::vec3 lightPos;

    ResourceManager* resourceManager;

private:

    void updateLightPosition() const;

    void drawStaticModels();

    void updateMatrices(const StaticModel &model) const;

    inline void setShaderProgram(GLuint shader_programme) const;

public:

    void init();

    std::vector<StaticModel> staticModels;

    void draw();

    Renderer();

    ~Renderer();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void key_callback_static(GLFWwindow *window, int key, int scancode, int action, int mods);


};


#endif //TESTGLEW_RENDERER_H


